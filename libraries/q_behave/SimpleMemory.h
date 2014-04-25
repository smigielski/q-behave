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

#ifndef SIMPLEMEMORY_H_
#define SIMPLEMEMORY_H_

#include "Memory.h"

namespace q_learning {

/**
 * Simple memory that retrieves and store state quantity in internal preallocated memory.
 */
class SimpleMemory: public Memory {
public:
	SimpleMemory(StateMap _stateMap, double* _internalMemmory[]);
private:
	virtual void storeInternal(int memoryNumber);
	virtual void loadInternal(int memoryNumber);
	double** internalMemmory;
};

} /* namespace q_learning */

#endif /* SIMPLEMEMORY_H_ */
