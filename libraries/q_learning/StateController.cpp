/*
 * Brain.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: marek
 */
#ifndef _TEST_
#include <Arduino.h>
#else
#include "mock_arduino.h"
#endif

#include "StateController.h"

namespace q_learning {

StateController::StateController(Memory _memory, double _restartPenalty){
	this->memory=_memory;
	this->restartPenalty=_restartPenalty;
#ifdef _INFO_
	Serial.println("[INFO] Brain created.");
#endif
}

StateController::~StateController() {

}

void StateController::start(int impulse,State* startState) {
#ifdef _INFO_
	Serial.print("[INFO] Starting activity for impulse: ");Serial.println(impulse);
#endif
	//check current state and react if in the middle of activity
	if (currentState != startState) {
		if (memory.loadMemory(impulse)) {
			stop(restartPenalty);
		} else {
			stop(0);
		}

		currentState = currentState->switchTo(startState);
	}

	//choose action
	invokeNextAction();

}

void StateController::stop(double amount) {

#ifdef _INFO_
	Serial.print("[INFO] Stopping activity, reward: ");Serial.println(amount);
#endif
	currentAction->quality = getUpdatedQuality(amount, currentAction->quality,currentAction->state);
#ifdef _DEBUG_
	Serial.print("[INFO] New reward for state: ");Serial.print(currentAction->state->getStateName());Serial.print(" is ");Serial.println("currentAction->quality");
#endif
}


void StateController::invokeNextAction() {
#ifdef _INFO_
	Serial.println("[INFO] Invoking next action");
#endif
	StateActions stateActions = memory.getStateActions(currentState);
	currentAction = getNextAction(stateActions);
	currentState = currentState->switchTo(currentAction->state);
}





} /* namespace q_learning */
