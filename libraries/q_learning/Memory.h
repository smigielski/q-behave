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



class Memory {
public:
	Memory(StateMap _stateMap, double* _internalMemmory[]);
	virtual ~Memory();
	StateActions getStateActions(State* state);
	bool loadMemory(int memoryNumber);
private:
	StateMap stateMap;
	int currentMap;
	double** internalMemmory;

	void storeInternal(int memoryNumber);
	void loadInternal(int memoryNumber);
};

} /* namespace q_learning */

#endif /* MEMORY_H_ */
