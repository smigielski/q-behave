/*
 * Brain.h
 *
 *  Created on: Apr 4, 2014
 *      Author: marek
 */
#include "State.h"

#ifndef BRAIN_H_
#define BRAIN_H_

namespace q_learning {

struct Action {
  State* state;
  double quality;
};

struct StateActions {
	State* state;
	int actionCount;
	Action* actions;
};

struct StateMap {
	int stateCount;
	StateActions* states;
};


class Brain {
public:
	Brain(State* _startState, StateMap _memory);
	virtual ~Brain();
	void start(int impulse);
	void stop(double amount);
	State* currentState;
private:
	//learning rate
	double alpha=0.1;
	//future discount
	double gamma =0.9;
	State* startState;
	Action* currentAction;
	int memoryGraphNumber;
	StateMap memory;
	virtual void invokeNextAction();
	virtual void loadMemory(int graphNumber);
	virtual Action* getNextAction(State* currentState);
	double getMaxReward(State* currentState);
	StateActions getStateActions(State* state);
};

} /* namespace q_learning */

#endif /* BRAIN_H_ */
