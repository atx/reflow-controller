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
#include "uip.h"
#include "uip_arp.h"
#include "evtimer.h"
#include "hal.h"
#include "lm75.h"
#include "max6675.h"
#include "enc.h"
#include "oven.h"
#include "temperature.h"

static EVENTSOURCE_DECL(enc_int_es);

static void enc_int(EXTDriver *drv, expchannel_t c)
{
	(void)drv;
	(void)c;
	chEvtBroadcast(&enc_int_es);
}

static const EXTConfig extcfg = {
	{
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_FALLING_EDGE | EXT_MODE_GPIOA | EXT_CH_MODE_AUTOSTART, enc_int},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
	}
};

struct enc enc = {
	.driver = &SPID1,
	.config = {
		NULL,
		GPIOA,
		4,
		SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2,
		SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2,
	},
	.mac = {
		ETHADDR0, ETHADDR1, ETHADDR2, ETHADDR3, ETHADDR4, ETHADDR5,
	}
};

static const struct uip_eth_addr macaddr = {
	{ETHADDR0, ETHADDR1, ETHADDR2, ETHADDR3, ETHADDR4, ETHADDR5}
};

#define EVID_NET_INT		0
#define EVID_NET_PERIODIC	1
#define EVID_NET_ARP		2

static void network_send()
{
	if (uip_len <= UIP_LLH_LEN + 40)
		enc_packet_send(&enc, uip_len, uip_buf, 0, NULL);
	else
		enc_packet_send(&enc, 54, uip_buf,
				uip_len - UIP_LLH_LEN - 40, uip_appdata);
}

static WORKING_AREA(network_wa, 512);
static msg_t network_thread(void *arg)
{
	EvTimer per_evt;
	EvTimer arp_evt;
	EventListener per_el;
	EventListener arp_el;
	EventListener int_el;
	uip_ipaddr_t ip;
	eventmask_t event;
	int i;
	uint8_t flags;

	(void)arg;

	evtInit(&per_evt, MS2ST(500));
	evtInit(&arp_evt, S2ST(10));

	chEvtRegister(&enc_int_es, &int_el, EVID_NET_INT);
	chEvtRegister(&per_evt.et_es, &per_el, EVID_NET_PERIODIC);
	chEvtRegister(&arp_evt.et_es, &arp_el, EVID_NET_ARP);

	enc_init(&enc);
	uip_init();
	uip_setethaddr(macaddr);
	uip_ipaddr(ip, IPADDR0, IPADDR1, IPADDR2, IPADDR3);
	uip_sethostaddr(ip);
	uip_listen(HTONS(80));

	evtStart(&per_evt);
	evtStart(&arp_evt);

	while (TRUE) {
		if (!palReadPad(GPIOA, GPIOA_ENC_INT)) {
			event = EVENT_MASK(EVID_NET_INT);
		} else {
			palClearPad(GPIOB, GPIOB_LED_SYS);
			event = chEvtWaitAny(ALL_EVENTS);
			palSetPad(GPIOB, GPIOB_LED_SYS);
		}
		if (event == EVENT_MASK(EVID_NET_INT)) {
			/* The interrupt line is low for as long as we have packets pending */
			flags = enc_int_flags(&enc);
			if (flags & ENC_PKTIF) {
				while ((uip_len = enc_packet_receive(&enc, UIP_BUFSIZE, uip_buf)) != 0) {
					switch(ntohs((((struct uip_eth_hdr *)&uip_buf[0])->type))) {
					case UIP_ETHTYPE_IP:
						uip_arp_ipin();
						uip_input();
						if (uip_len > 0) {
							uip_arp_out();
							network_send();
						}
						break;
					case UIP_ETHTYPE_ARP:
							uip_arp_arpin();
							if (uip_len > 0)
								network_send();
						break;
					default: /* This usually happens on overflows, hackish but works */
						enc_init(&enc);
						break;
					}
				}
			}
			enc_int_clear(&enc, ENC_ALLIF);
			/* TODO: This patches the race condition, fix... */
			chThdSleepMicroseconds(100);
		} else if (event == EVENT_MASK(EVID_NET_PERIODIC)) {
			for (i = 0; i < UIP_CONNS; i++) {
				uip_periodic(i);
				if (uip_len > 0) {
					uip_arp_out();
					network_send();
				}
			}
		} else {
			uip_arp_timer();
		}
	}

	return 0;
}

static WORKING_AREA(temperature_wa, 128);
static WORKING_AREA(oven_wa, 128);

int main(void)
{
	halInit();
	chSysInit();

	i2cInit();
	spiInit();
	extInit();

	chEvtInit(&enc_int_es);
	extStart(&EXTD1, &extcfg);

	chThdCreateStatic(temperature_wa, sizeof(temperature_wa), NORMALPRIO,
			temperature_thread, NULL);
	chThdCreateStatic(network_wa, sizeof(network_wa), NORMALPRIO, network_thread, NULL);
	chThdCreateStatic(oven_wa, sizeof(oven_wa), NORMALPRIO, oven_thread, NULL);

	chThdExit(0);
	return 0;
}
