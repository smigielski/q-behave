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

#include "Brain.h"

namespace q_learning {

Brain::Brain(State* _startState, StateMap _memory) {
	this->startState = _startState;
	this->currentState = _startState;
	this->memory = _memory;
	memoryGraphNumber = 0;
#ifdef _INFO_
	Serial.println("[INFO] Brain created.");
#endif
}

Brain::~Brain() {
}

void Brain::start(int impulse) {
#ifdef _INFO_
	Serial.print("[INFO] Starting activity for impulse: ");Serial.println(impulse);
#endif
	//check current state and react if in the middle of activity
	if (currentState != startState) {
		stop(-5.0);
	}
	//find correct q-learning graph
	if (memoryGraphNumber != impulse) {
		loadMemory(impulse);
	}
	//choose action
	invokeNextAction();

}

void Brain::stop(double amount) {

#ifdef _INFO_
	Serial.print("[INFO] Stopping activity, reward: ");Serial.println(amount);
#endif

	currentAction->quality = currentAction->quality
			+ alpha
					* (amount + gamma * getMaxReward(currentAction->state)
							- currentAction->quality);
	currentState = currentState->switchTo(this->startState);
#ifdef _DEBUG_
	Serial.print("[INFO] New reward for state: ");Serial.print(currentAction->state->getStateName());Serial.print(" is ");Serial.println("currentAction->quality");
#endif
}

void Brain::loadMemory(int memoryNumber) {

#ifdef _INFO_
	Serial.print("[INFO] Loading memory: ");Serial.println(memoryNumber);
#endif
	//TODO load memory
}

void Brain::invokeNextAction() {
#ifdef _INFO_
	Serial.println("[INFO] Invoking next action");
#endif
	currentAction = getNextAction(currentState);
	currentState = currentState->switchTo(currentAction->state);
}

Action* Brain::getNextAction(State* currentState) {
#ifdef _DEBUG_
	Serial.println("[DEBUG] Get next action");
#endif
	StateActions stateActions = getStateActions(currentState);
	double maxQuality = stateActions.actions[0].quality;
	Action* nextAction = &stateActions.actions[0];
	for (int i = 0; i < stateActions.actionCount; i++) {
		if (stateActions.actions[i].quality > maxQuality) {
			maxQuality = stateActions.actions[i].quality;
			nextAction = &stateActions.actions[i];
		}
	}
#ifdef _DEBUG_
	Serial.print("[DEBUG] Returning action leading to: ");Serial.print(nextAction->state->getStateName());Serial.print(" (");Serial.print(maxQuality);Serial.println(")");
#endif
	return nextAction;
}

double Brain::getMaxReward(State* state) {
	StateActions stateActions = getStateActions(state);
	double maxQuality = stateActions.actions[0].quality;
	Action nextAction = stateActions.actions[0];
	for (int i = 0; i < stateActions.actionCount; i++) {
		if (stateActions.actions[i].quality > maxQuality) {
			maxQuality = stateActions.actions[i].quality;
			nextAction = stateActions.actions[i];
		}
	}
#ifdef _DEBUG_
	Serial.print("[DEBUG] Returning future max reward for state ");Serial.print(nextAction.state->getStateName());Serial.print(" (");Serial.print("maxQuality");Serial.println(")");
#endif
	return maxQuality;
}

StateActions Brain::getStateActions(State* state) {
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
