/*
 * RestState.h
 *
 *  Created on: Apr 4, 2014
 *      Author: marek
 */

#ifndef RESTSTATE_H_
#define RESTSTATE_H_

#include "State.h"

namespace q_learning {

class RestState: public q_learning::State {
public:
	RestState();
	virtual ~RestState();
	virtual char* getStateName();
	virtual void activate();
	virtual void deactivate();
};

} /* namespace q_learning */

#endif /* RESTSTATE_H_ */
