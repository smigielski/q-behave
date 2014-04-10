/*
 * QLearningMachine.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: marek
 */
#ifndef _TEST_
#include <Arduino.h>
#else
#include "mock_arduino.h"
#endif

#include "QLearningMachine.h"

namespace q_learning {

QLearningMachine::QLearningMachine(State* _startState, StateMap _memory, double _restartPenalty) : StateController(_startState,  _memory,  _restartPenalty){
	//learning definition
	this->learningRate=0.1;
	this->discountRate=0.9;
}

QLearningMachine::~QLearningMachine() {

}

Action* QLearningMachine::getNextAction(StateActions stateActions) {
#ifdef _DEBUG_
	Serial.println("[DEBUG] Get next action");
#endif

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

double QLearningMachine::getUpdatedQuality(double amount, double quality, State* state){
	double newQuality = quality
			+ learningRate
					* (amount + discountRate * getMaxReward(state)
							- quality);

	return newQuality;
}

double QLearningMachine::getMaxReward(State* state) {
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

} /* namespace q_learning */
