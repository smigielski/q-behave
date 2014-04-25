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


#ifndef QLEARNINGMACHINE_H_
#define QLEARNINGMACHINE_H_

#include "StateController.h"

namespace q_behave {
/**
 * Q-Learning algorithm implementation.
 * It randomize action choices according to Boltzmann-Gibbs rule.
 */
class QLearningMachine: public q_behave::StateController {
public:
	QLearningMachine(Memory* _memory,  State* _startState);
private:
	double learningRate;
	double discountRate;
	double randomizationTemperature;

	virtual Action* getNextAction(StateActions stateActions);
	virtual double getUpdatedQuality(double amount, double quality, State* state);

	double getMaxReward(State* currentState);
	double calculateExp(double q);

};

} /* namespace q_behave */

#endif /* QLEARNINGMACHINE_H_ */
