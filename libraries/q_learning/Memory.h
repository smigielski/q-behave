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

#ifndef MEMORY_H_
#define MEMORY_H_

#include "State.h"

namespace q_learning {

/**
 * Structure to hold state and quality estimate for the action
 */
struct Action {
	State* state;
	double quality;
};

/**
 * State to action map. It hold links to all possible action from one state.
 * If it is end action is should reference to itself.
 */
struct StateActions {
	State* state;
	int actionCount;
	Action* actions;
};

/**
 * Diagram of all actions in the system
 */
struct StateMap {
	int stateCount;
	StateActions* states;
};

/**
 * Base memory class. It has to be subclass to provide different memory storage.
 */
class Memory {
public:
	Memory(StateMap _stateMap);
	virtual ~Memory();
	StateActions getStateActions(State* state);
	bool loadMemory(int memoryNumber);
	StateMap stateMap;
private:

	int currentMap;
	virtual void storeInternal(int memoryNumber) = 0;
	virtual void loadInternal(int memoryNumber) = 0;
};

} /* namespace q_learning */

#endif /* MEMORY_H_ */
