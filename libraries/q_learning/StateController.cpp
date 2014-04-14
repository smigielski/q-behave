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

#ifndef _TEST_
#include <Arduino.h>
#else
#include "mock_arduino.h"
#endif

#include "StateController.h"

namespace q_learning {

StateController::StateController(Memory* _memory) {
	this->memory = _memory;
	this->currentState = 0;
	this->currentAction = 0;
#ifdef _INFO_
	Serial.println("[INFO] Brain created.");
#endif
}

void StateController::start(int impulse, State* startState) {
#ifdef _INFO_
	Serial.println("--------------------------------------");
	Serial.print("[INFO] Starting activity for impulse: ");
	Serial.println(impulse);
#endif
	//check current state and react if in the middle of activity
	memory->loadMemory(impulse);

	if (currentState != 0 && currentState != startState) {
		stop(0);
		currentState = currentState->switchTo(startState);
	} else {
		currentState = startState;
	}
	//choose action
	invokeNextAction();

}

void StateController::stop(double amount) {

#ifdef _INFO_
	Serial.print("[INFO] Stopping activity, reward: ");
	Serial.println(amount);
#endif
	currentAction->quality = getUpdatedQuality(amount, currentAction->quality,
			currentAction->state);
#ifdef _DEBUG_
	Serial.print("[INFO] New reward for state: ");
	Serial.print(currentAction->state->getStateName());
	Serial.print(" is ");
	Serial.println("currentAction->quality");
#endif
}

void StateController::invokeNextAction() {
#ifdef _INFO_
	Serial.println("[INFO] Invoking next action");
#endif
	StateActions stateActions = memory->getStateActions(currentState);
	currentAction = getNextAction(stateActions);
	currentState = currentState->switchTo(currentAction->state);
}

} /* namespace q_learning */
