/*
 * QLearningMachine.h
 *
 *  Created on: Apr 10, 2014
 *      Author: marek
 */

#ifndef QLEARNINGMACHINE_H_
#define QLEARNINGMACHINE_H_

#include "StateController.h"

namespace q_learning {

class QLearningMachine: public q_learning::StateController {
public:
	QLearningMachine(State* _startState, StateMap _memory, double _restartPenalty=-5.0);
	virtual ~QLearningMachine();
private:
	double learningRate;
	double discountRate;

	virtual Action* getNextAction(StateActions stateActions);
	virtual double getUpdatedQuality(double amount, double quality, State* state);

	double getMaxReward(State* currentState);

};

} /* namespace q_learning */

#endif /* QLEARNINGMACHINE_H_ */
