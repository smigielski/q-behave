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
#include "math.h";
#include "QLearningMachine.h"

namespace q_learning {

QLearningMachine::QLearningMachine(Memory* _memory,  State* _startState) : StateController(_memory,_startState){
	//learning definition
	this->learningRate=0.1;
	this->discountRate=0.9;
	this->randomizationTemperature=2.0;
}


Action* QLearningMachine::getNextAction(StateActions stateActions) {
#ifdef _DEBUG_
	Serial.println("[DEBUG] Get next action");
#endif

	double sigma = 0;
	Action* nextAction = &stateActions.actions[0];
	for (int i = 0; i < stateActions.actionCount; i++) {
		sigma += calculateExp(stateActions.actions[i].quality);
	}
	//This idea leads to softmax methods [78, 79]. One of the most widely used softmax methods is Boltzmann-Gibbs rule which chooses action a with probability
	int rand = random(100)+1;
	int sum=0;
	double maxQuality;
	int i = 0;
	while (sum<rand){
		nextAction = &stateActions.actions[i];
		maxQuality = calculateExp(stateActions.actions[i].quality)/sigma*100;
		sum+= maxQuality;
		i++;
	}
#ifdef _DEBUG_
	Serial.print("[DEBUG] Returning action leading to: ");Serial.print(nextAction->state->getStateName());Serial.print(" (");Serial.print(maxQuality);Serial.println(")");
#endif
	return nextAction;
}


double QLearningMachine::calculateExp(double q){
	return exp( q/randomizationTemperature );
}

double QLearningMachine::getUpdatedQuality(double amount, double quality, State* state){
	double newQuality = quality
			+ learningRate
					* (amount + discountRate * getMaxReward(state)
							- quality);

	return newQuality;
}

double QLearningMachine::getMaxReward(State* state) {
	StateActions stateActions = memory->getStateActions(state);
	double maxQuality = stateActions.actions[0].quality;
	Action nextAction = stateActions.actions[0];
	for (int i = 0; i < stateActions.actionCount; i++) {
		if (stateActions.actions[i].quality > maxQuality) {
			maxQuality = stateActions.actions[i].quality;
			nextAction = stateActions.actions[i];
		}
	}
#ifdef _DEBUG_
	Serial.print("[DEBUG] Returning future max reward for state ");Serial.print(nextAction.state->getStateName());Serial.print(" (");Serial.print(maxQuality);Serial.println(")");
#endif
	return maxQuality;
}

} /* namespace q_learning */
