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

#include "mock_arduino.h"
#include "../libraries/q_learning/QLearningMachine.h"
#include "../libraries/q_learning/RestState.h"
#include "../libraries/q_learning/MockState.h"
#include "../libraries/q_learning/SimpleMemory.h"
#include <string.h>
#include <stdlib.h>

using namespace q_learning;

int mock1state = 0;
int mock2state = 0;

RestState restState = RestState();
MockState mock1 = MockState("mock1", &mock1state);
MockState mock2 = MockState("mock2", &mock2state);

Action restActions[] = { { &mock1, 0.0 }, { &mock2, 0.0 } };
Action mock1Actions[] = { { &mock1, 0.0 } };
Action mock2Actions[] = { { &mock2, 0.0 } };

StateActions states[] = { { &restState, 2, restActions }, { &mock1, 1,
		mock1Actions }, { &mock2, 1, mock2Actions } };
StateMap stateMap = { 3, states };

double prob1[4], prob2[4], prob3[4];
double* internalMemmory[] = { prob1, prob2, prob3 };

void testMock2(StateController& brain) {

	int success1 = 0;
	int count1 = 0;
	while (success1 < 5 && count1 < 1000) {
		brain.start(0, &restState);
		count1++;
		if (brain.currentState == &mock2) {
			brain.stop(10.0);
			success1++;
		} else {
			success1 = 0;
		}
	}
	brain.start(0, &restState);
	if (mock1state != 0 || mock2state != 1) {
#ifdef _ERROR_
		Serial.print("[ERROR] Mock2 should be learned! Mock1: ");
		Serial.print(mock1state);
		Serial.print(" Mock2: ");
		Serial.println(mock2state);
		exit(1);
#endif
	}
	brain.stop(10.0);
#ifdef _INFO_
	Serial.print("[INFO] Mock2 count: ");
	Serial.print(count1);
	Serial.print(", success: ");
	Serial.println(success1);
#endif

}

void testMock1(StateController& brain) {

	int success1 = 0;
	int count1 = 0;
	while (success1 < 5 && count1 < 1000) {
		brain.start(0, &restState);
		count1++;
		if (brain.currentState == &mock2) {
			brain.stop(10.0);
			success1++;
		} else {
			success1 = 0;
		}
	}
	brain.start(0, &restState);
	if (mock1state != 0 || mock2state != 1) {
#ifdef _ERROR_
		Serial.print("[ERROR] Mock2 should be learned! Mock1: ");
		Serial.print(mock1state);
		Serial.print(" Mock2: ");
		Serial.println(mock2state);
		exit(1);
#endif
	}
	brain.stop(10.0);

	int success2 = 0;
	int count2 = 0;
	while (success2 < 5 && count2 < 1000) {
		brain.start(0, &restState);
		count2++;
		if (brain.currentState == &mock1) {
			brain.stop(10.0);
			success2++;
		} else {
			brain.stop(-10.0);
			success2 = 0;
		}
	}
	brain.start(0, &restState);
	if (mock1state != 1 || mock2state != 0) {
#ifdef _ERROR_
		Serial.print("[ERROR] Mock1 should be learned! Mock1: ");
		Serial.print(mock1state);
		Serial.print(" Mock2: ");
		Serial.println(mock2state);
		exit(1);
#endif
	}
	brain.stop(10.0);
#ifdef _INFO_
	Serial.print("[INFO] Mock1 count: ");
	Serial.print(count2);
	Serial.print(", success: ");
	Serial.println(success2);
#endif

}

void testMock2and1(StateController& brain) {

	int success1 = 0;
	int count1 = 0;
	while (success1 < 5 && count1 < 1000) {
		brain.start(1, &restState);
		count1++;
		if (brain.currentState == &mock2) {
			brain.stop(10.0);
			success1++;
		} else {
			success1 = 0;
		}
	}
	brain.start(1, &restState);
	if (mock1state != 0 || mock2state != 1) {
#ifdef _ERROR_
		Serial.print("[ERROR] Mock2 should be learned! Mock1: ");
		Serial.print(mock1state);
		Serial.print(" Mock2: ");
		Serial.println(mock2state);
		exit(1);
#endif
	}
	brain.stop(10.0);

	int success2 = 0;
	int count2 = 0;
	while (success2 < 5 && count2 < 1000) {
		brain.start(2, &restState);
		count2++;
		if (brain.currentState == &mock1) {
			brain.stop(10.0);
			success2++;
		} else {
			success2 = 0;
		}
	}

	//Check that 0 memory holds mock1 state
	brain.start(1, &restState);
	if (mock1state != 0 || mock2state != 1) {
#ifdef _ERROR_
		Serial.print(
				"[ERROR] For 1 memory bank Mock2 should be learned! Mock1: ");
		Serial.print(mock1state);
		Serial.print(" Mock2: ");
		Serial.println(mock2state);
		exit(1);
#endif
	}
	brain.stop(10.0);

	//Check that 1 memory holds mock2 state
	brain.start(2, &restState);
	if (mock1state != 1 || mock2state != 0) {
#ifdef _ERROR_
		Serial.print(
				"[ERROR] For 2 memory bank Mock1 should be learned! Mock1: ");
		Serial.print(mock1state);
		Serial.print(" Mock2: ");
		Serial.println(mock2state);
		exit(1);
#endif
	}
	brain.stop(10.0);

#ifdef _INFO_
	Serial.print("[INFO] Mock1 count: ");
	Serial.print(count2);
	Serial.print(", success: ");
	Serial.println(success2);
#endif

}
int main(int argc, char **argv) {
	SimpleMemory memory = SimpleMemory(stateMap, internalMemmory);
	QLearningMachine brain = QLearningMachine(&memory);
	//test simple learning
	testMock2(brain);
	//test learning second thing after learning one
	testMock1(brain);

	QLearningMachine brain2 = QLearningMachine(&memory);

	testMock2(brain2);

	//test learning two things at the same time
	testMock2and1(brain);

}
