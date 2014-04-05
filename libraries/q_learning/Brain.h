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
	void reward(int amount=100);
	void punish(int amount=100);
	void stop(int amount=10);
private:
	State* startState;
	State* currentState;
	int memoryGraphNumber;
	StateMap memory;
	virtual void invokeNextAction();
	virtual void loadMemmory(int graphNumber);
	virtual State* getNextAction(State* currentState);
	StateActions getStateActions(State* state);
};

} /* namespace q_learning */

#endif /* BRAIN_H_ */
