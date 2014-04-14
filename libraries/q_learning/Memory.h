/*
 * Memory.h
 *
 *  Created on: Apr 10, 2014
 *      Author: marek
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "State.h"

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

struct Segment {
	int memoryNumber;
	StateMap states;
	Segment* next;
};

class Memory {
public:
	Memory(StateMap main);
	virtual ~Memory();

	StateActions getStateActions(State* state);
	bool loadMemory(int memoryNumber);
private:
	Segment* firstSegment;
};

} /* namespace q_learning */

#endif /* MEMORY_H_ */
