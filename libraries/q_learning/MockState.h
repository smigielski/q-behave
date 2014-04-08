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
	MockState(char* stateName,int* _state);
	virtual ~MockState();
	virtual char* getStateName();
	virtual void activate();
	virtual void deactivate();
private:
	char* stateName;
	int* state;
};

} /* namespace q_learning */

#endif /* MOCKSTATE_H_ */
