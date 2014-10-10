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


#include "max6675.h"
#include "hal.h"

int max6675_get_temp(const struct max6675 *max)
{
	uint16_t read;

	spiAcquireBus(max->driver);
	spiStart(max->driver, &max->config);
	spiSelect(max->driver);
	spiReceive(max->driver, 1, &read);
	spiUnselect(max->driver);
	spiStop(max->driver);
	spiReleaseBus(max->driver);

	return (read >> 3) * 250;
}
