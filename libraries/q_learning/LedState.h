/*
 * LedState.h
 *
 *  Created on: Apr 4, 2014
 *      Author: marek
 */

#ifndef LEDSTATE_H_
#define LEDSTATE_H_

#include "State.h"

namespace q_learning {

class LedState: public q_learning::State {
public:
	LedState(char* _stateName,int pinNumber);
	virtual ~LedState();
	virtual char* getStateName();
	virtual void activate();
	virtual void deactivate();
private:
	char* stateName;
	int pin;
};

} /* namespace q_learning */

#endif /* LEDSTATE_H_ */
