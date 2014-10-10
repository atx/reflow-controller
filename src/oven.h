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

#ifndef __OVEN_H__
#define __OVEN_H__

struct oven_entry {
	int time;
	int temp;
};

/* Set time to OVEN_ENTRY_INVALID for all invalid entries */
#define OVEN_ENTRY_INVALID -1

#define OVEN_PROFILE_MAXLEN 16

/* TODO: We should encapsulate this or at least add mutex */
extern struct oven_entry oven_profile[OVEN_PROFILE_MAXLEN];

int oven_current_time();
int oven_current_target();
bool oven_is_running();

/* This function also restarts the oven if it is already running */
void oven_start();
void oven_stop();

msg_t oven_thread();

#endif
