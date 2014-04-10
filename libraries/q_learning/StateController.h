/*
 * Brain.h
 *
 *  Created on: Apr 4, 2014
 *      Author: marek
 */
#include "State.h"

#ifndef STATECONTROLLER_H_
#define STATECONTROLLER_H_

#define _DEBUG_
#define _INFO_
#define _ERROR_

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


class StateController {
public:
	StateController(State* _startState, StateMap _memory, double _restartPenalty=-5.0);
	virtual ~StateController();
	void start(int impulse);
	void stop(double amount);
	StateActions getStateActions(State* state);
	State* currentState;
private:
	double restartPenalty;
	State* startState;
	Action* currentAction;
	int memoryGraphNumber;
	StateMap memory;
	virtual void invokeNextAction();
	virtual void loadMemory(int graphNumber);
	virtual Action* getNextAction(StateActions stateActions) = 0;
	virtual double getUpdatedQuality(double amount, double quality, State* state)=0;
};

} /* namespace q_learning */

#endif /* STATECONTROLLER_H_ */
