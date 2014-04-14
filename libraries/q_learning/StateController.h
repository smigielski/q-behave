/*
 * Brain.h
 *
 *  Created on: Apr 4, 2014
 *      Author: marek
 */


#ifndef STATECONTROLLER_H_
#define STATECONTROLLER_H_

#include "State.h"
#include "Memory.h"

#define _DEBUG_
#define _INFO_
#define _ERROR_

namespace q_learning {


class StateController {
public:
	StateController(Memory _memory, double _restartPenalty=-5.0);
	virtual ~StateController();
	void start(int impulse, State* startState);
	virtual void invokeNextAction();
	void stop(double amount);
	State* currentState;
private:
	double restartPenalty;
	Action* currentAction;
	Memory memory;

	virtual Action* getNextAction(StateActions stateActions) = 0;
	virtual double getUpdatedQuality(double amount, double quality, State* state)=0;
};

} /* namespace q_learning */

#endif /* STATECONTROLLER_H_ */
