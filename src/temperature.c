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
#include "lm75.h"
#include "max6675.h"
#include "temperature.h"
#include "util.h"

EVENTSOURCE_DECL(temperature_event);

static const struct lm75 lm75 = {
	.driver = &I2CD2,
	.config = {
		0x1042C30F,
		0,
		0,
	},
	.addr = 0b1001000,
};

static const struct max6675 max6675 = {
	.driver = &SPID2,
	.config = {
		NULL,
		GPIOB,
		GPIOB_MAX_CS,
		SPI_CR1_RXONLY | SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2,
		SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2 | SPI_CR2_DS_3,
	},
};

volatile int temperature_oven;
volatile int temperature_board;

msg_t temperature_thread(void *arg)
{
	int oacc[3];
	int bacc[3];
	int i;

	(void)arg;

	for (i = 0; ; i = (i + 1) % 3) {
		oacc[i] = max6675_get_temp(&max6675);
		bacc[i] = lm75_get_temp(&lm75);
		if (i == 2) {
			temperature_oven = max(oacc[0], max(oacc[1], oacc[2]));
			temperature_board = max(bacc[0], max(bacc[1], bacc[2]));
			chEvtBroadcast(&temperature_event);
		}
		chThdSleepMilliseconds(250);
	}
	return 0;
}
