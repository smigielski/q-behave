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

StateController::StateController(State* _startState, StateMap _memory, double _restartPenalty) : memoryMangger(_memory){
	this->startState = _startState;
	this->currentState = _startState;
	this->memoryGraphNumber = 0;
	this->memory=memoryMangger.getMemory(memoryGraphNumber);

	this->restartPenalty=_restartPenalty;

#ifdef _INFO_
	Serial.println("[INFO] Brain created.");
#endif
}

StateController::~StateController() {

}

void StateController::start(int impulse) {
#ifdef _INFO_
	Serial.print("[INFO] Starting activity for impulse: ");Serial.println(impulse);
#endif
	//check current state and react if in the middle of activity
	if (currentState != startState) {
		if (memoryGraphNumber != impulse) {
			stop(0);
			loadMemory(impulse);
		} else {
			stop(restartPenalty);
		}
	}

	//choose action
	invokeNextAction();

}

void StateController::stop(double amount) {

#ifdef _INFO_
	Serial.print("[INFO] Stopping activity, reward: ");Serial.println(amount);
#endif

	currentAction->quality = getUpdatedQuality(amount, currentAction->quality,currentAction->state);
	currentState = currentState->switchTo(this->startState);
#ifdef _DEBUG_
	Serial.print("[INFO] New reward for state: ");Serial.print(currentAction->state->getStateName());Serial.print(" is ");Serial.println("currentAction->quality");
#endif
}


void StateController::loadMemory(int memoryNumber) {

#ifdef _INFO_
	Serial.print("[INFO] Loading memory: ");Serial.println(memoryNumber);
#endif
	memory = memoryMangger.getMemory(memoryNumber);
	memoryGraphNumber=memoryNumber;
}

void StateController::invokeNextAction() {
#ifdef _INFO_
	Serial.println("[INFO] Invoking next action");
#endif
	StateActions stateActions = getStateActions(currentState);
	currentAction = getNextAction(stateActions);
	currentState = currentState->switchTo(currentAction->state);
}



StateActions StateController::getStateActions(State* state) {
#ifdef _DEBUG_
	Serial.print("[DEBUG] Get state actions for state: ");Serial.println(state->getStateName());
#endif
	for (int i = 0; i < memory.stateCount; i++) {
		if (memory.states[i].state == state) {
			return memory.states[i];
		}
	}
#ifdef _ERROR_
	Serial.println("[ERROR] No state action found. Wrong configuration");
#endif
}

} /* namespace q_learning */
