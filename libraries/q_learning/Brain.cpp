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
	Serial.write("[INFO] Brain created.");
#endif
}

Brain::~Brain() {
}

void Brain::start(int impulse) {
#ifdef _INFO_
	char myConcatenation[80];
	sprintf(myConcatenation,"[INFO] Starting activity for impulse: %i",impulse);
	Serial.write(myConcatenation);
#endif
	//check current state and react if in the middle of activity
	if (currentState != startState) {
		stop();
	}
	//find correct q-learning graph
	if (memoryGraphNumber != impulse) {
		loadMemmory(impulse);
	}
	//choose action
	invokeNextAction();

}

void Brain::reward(int amount) {
//TODO implement
}
void Brain::punish(int amount) {
	//TODO implement
}

void Brain::stop(int amount) {
#ifdef _INFO_
	char myConcatenation[80];
	sprintf(myConcatenation,"[INFO] Stopping activity, reward: %i",amount);
	Serial.write(myConcatenation);
#endif
}

void Brain::loadMemmory(int memoryNumber) {

#ifdef _INFO_
	char myConcatenation[80];
	sprintf(myConcatenation,"[INFO] Loading memory: %i",memoryNumber);
	Serial.write(myConcatenation);
#endif
	//TODO load memmory
}

void Brain::invokeNextAction() {
#ifdef _INFO_
	Serial.write("[INFO] Invoking next action");
#endif
	State* nextAction = getNextAction(currentState);
	currentState = currentState->switchTo(nextAction);
}

State* Brain::getNextAction(State* currentState) {
#ifdef _DEBUG_
	Serial.write("[DEBUG] Get next action");
#endif
	StateActions stateActions = getStateActions(currentState);
	double maxQuality = stateActions.actions[0].quality;
	State* nextAction = stateActions.actions[0].state;
	for (int i = 0; i < stateActions.actionCount; i++) {
		if (stateActions.actions[i].quality > maxQuality) {
			maxQuality = stateActions.actions[i].quality;
			nextAction = stateActions.actions[i].state;
		}
	}
#ifdef _DEBUG_
	char myConcatenation[80];
	sprintf(myConcatenation,"[DEBUG] Returning action leading to: %s (%f)",nextAction->getStateName(),maxQuality);
	Serial.write(myConcatenation);
#endif
	return nextAction;
}

StateActions Brain::getStateActions(State* state) {
#ifdef _DEBUG_
	char myConcatenation[80];
	sprintf(myConcatenation,"[DEBUG] Get state actions for state:  %s",state->getStateName());
	Serial.write(myConcatenation);
#endif
	for (int i = 0; i < memory.stateCount; i++) {
		if (memory.states[i].state == state) {
			return memory.states[i];
		}
	}
#ifdef _ERROR_
	Serial.write("[ERROR] No state action found. Wrong configuration");
#endif
}

} /* namespace q_learning */
