/*
 *  Copyright (C) Josef Gajdusek <atx@atx.name>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 */


#include "ch.h"
#include "chbsem.h"
#include "hal.h"
#include "oven.h"
#include "util.h"
#include "temperature.h"


static bool oven_running = false;
static int oven_time;
static bool oven_relays = false;
/* TODO Find appropriate name for this */
static int oven_thermal_speed = 0;

static BinarySemaphore oven_semaphore;

/* This MUST be sorted by time in ascending order and MUST be terminated with
 * OVEN_ENTRY_INVALID entry
 * */
struct oven_entry oven_profile[OVEN_PROFILE_MAXLEN] = {
	{ 0, 25 },
	{ 120, 130 },
	{ 210, 130 },
	{ 300, 200 },
	{ 400, 25 },
	{ OVEN_ENTRY_INVALID, OVEN_ENTRY_INVALID },
};

static int oven_profile_at(int t, bool *ended)
{
	unsigned int i = 0;

	while (i < ARRAY_SIZE(oven_profile) - 1 &&
			oven_profile[i + 1].time != OVEN_ENTRY_INVALID &&
			oven_profile[i].time < t) {
		i++;
	}

	if (oven_profile[i + 1].time == OVEN_ENTRY_INVALID
			&& oven_profile[i].time <= t)
		*ended = true;
	else
		*ended = false;

	return oven_profile[i].temp * 1000;
}

int oven_current_time()
{
	return oven_time;
}

bool oven_is_running()
{
	return oven_running;
}

void oven_start()
{
	oven_running = true;
	oven_time = 0;
	chBSemSignal(&oven_semaphore);
}

void oven_stop()
{
	oven_running = false;
}

/* We are in open-drain mode, so we need to clear if we want to turn the relays on */
static void oven_relay_on()
{
	palClearPad(GPIOB, GPIOB_HEAT_BOT);
	palClearPad(GPIOA, GPIOA_HEAT_TOP);
	palSetPad(GPIOB, GPIOB_LED_HEAT);
	oven_relays = true;
}

static void oven_relay_off()
{
	palSetPad(GPIOB, GPIOB_HEAT_BOT);
	palSetPad(GPIOA, GPIOA_HEAT_TOP);
	palClearPad(GPIOB, GPIOB_LED_HEAT);
	oven_relays = false;
}

#define HYSTERESIS		400
#define PREFETCH		20
#define MAX_OVEN_TEMP	270000
#define MAX_BOARD_TEMP	50000

msg_t oven_thread()
{
	systime_t next;
	int ctgt;
	bool ended;

	chBSemInit(&oven_semaphore, TRUE);

	while (TRUE) {
		oven_running = false;
		oven_relay_off();
		palClearPad(GPIOA, GPIOA_LED_PRG);

		chBSemWait(&oven_semaphore);

		oven_running = true;
		oven_time = false;
		oven_thermal_speed = 0;
		palSetPad(GPIOA, GPIOA_LED_PRG);

		next = chTimeNow();
		while (TRUE) {
			next += S2ST(1);

			ctgt = oven_profile_at(oven_time, &ended);

			if (ended || !oven_running ||
					(temperature_oven > MAX_OVEN_TEMP) ||
					(temperature_board > MAX_BOARD_TEMP))
				break;

			/* This is kind of bad
			 * TODO Generalize
			 * */

			oven_thermal_speed += oven_relays ? 1 : -1;
			oven_thermal_speed = clamp(0, oven_thermal_speed, 100);

			if (oven_thermal_speed < 50)
				ctgt = oven_profile_at(oven_time + PREFETCH, &ended);

			oven_time++;

			if (temperature_oven > (ctgt - HYSTERESIS * oven_thermal_speed))
				oven_relay_off();
			else
				oven_relay_on();

			chThdSleepUntil(next);
		}
	}

	return 0;
}
