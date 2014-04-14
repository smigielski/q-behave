/*
 * State machine with learning capabilities.
 *
 * Copyright (C) 2014 Poliprojekt.pl sp. z o.o.
 * Author: Marek Smigielski <marek.smigielski@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */



#ifndef STATECONTROLLER_H_
#define STATECONTROLLER_H_

#include "State.h"
#include "Memory.h"

#define _DEBUG_
#define _INFO_
#define _ERROR_

namespace q_learning {

/**
 * Main class controlling state machine and actions between them.
 */
class StateController {
public:
	StateController(Memory* _memory);


	void start(int impulse, State* startState);
	virtual void invokeNextAction();
	void stop(double amount);

	Memory* memory;
	State* currentState;
	Action* currentAction;

private:
	virtual Action* getNextAction(StateActions stateActions) = 0;
	virtual double getUpdatedQuality(double amount, double quality, State* state)=0;
};

} /* namespace q_learning */

#endif /* STATECONTROLLER_H_ */
