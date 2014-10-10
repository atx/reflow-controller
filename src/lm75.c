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

#include "hal.h"
#include "lm75.h"

int lm75_get_temp(const struct lm75 *lm)
{
	uint8_t rec[2];

	i2cAcquireBus(lm->driver);
	i2cStart(lm->driver, &lm->config);
	i2cMasterTransmit(lm->driver, lm->addr, (uint8_t[]){0}, 1, NULL, 0);
	i2cMasterReceive(lm->driver, lm->addr, rec, sizeof(rec));
	i2cStop(lm->driver);
	i2cReleaseBus(lm->driver);

	return ((rec[0] << 3) | (rec[1] >> 5)) * 125;
}
