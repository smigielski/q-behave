/*
 * MockState.h
 *
 *  Created on: Apr 5, 2014
 *      Author: marek
 */

#ifndef MOCKSTATE_H_
#define MOCKSTATE_H_

#include "State.h"

namespace q_learning {

class MockState: public q_learning::State {
public:
	MockState(char* stateName);
	virtual ~MockState();
	virtual char* getStateName();
	virtual State* switchTo(State* state);
	virtual void activate();
	virtual void deactivate();
private:
	char* stateName;
};

} /* namespace q_learning */

#endif /* MOCKSTATE_H_ */
