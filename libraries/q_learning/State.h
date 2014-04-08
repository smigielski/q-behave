/*
 * State.h
 *
 *  Created on: Apr 4, 2014
 *      Author: marek
 */

#ifndef STATE_H_
#define STATE_H_

namespace q_learning {

	class State {
	public:
		State();
		virtual ~State();
		State* switchTo(State* state);
		virtual char* getStateName() = 0;
		virtual void activate() = 0;
		virtual void deactivate() = 0;
	};

} /* namespace q_learning */

#endif /* STATE_H_ */
