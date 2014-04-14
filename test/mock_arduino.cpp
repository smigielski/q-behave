/*
 * State machine with learning capabilities.
 *
 * Copyright (C) 2014 Poliprojekt.pl sp. z o.o.
 * Author: Marek Smigielski <marek.smigielski@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <sys/timeb.h>
#include "mock_arduino.h"
#include "stdlib.h"

timeb t_start;
unsigned long millis() {
	timeb t_now;
	ftime(&t_now);
	return (t_now.time - t_start.time) * 1000
			+ (t_now.millitm - t_start.millitm);
}

void delay(unsigned long ms) {
	unsigned long start = millis();
	while (millis() - start < ms) {
	}
}

void initialize_mock_arduino() {
	ftime(&t_start);
}

long random(long howbig) {
	if (howbig == 0) {
		return 0;
	}
	return random() % howbig;
}
