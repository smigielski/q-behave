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

#ifndef _TEST_
#include <Arduino.h>
#else
#include "mock_arduino.h"
#endif

#include "Memory.h"

namespace q_behave {

Memory::Memory(StateMap _stateMap) {
	this->stateMap = _stateMap;
	currentMap = 0;
}

Memory::~Memory() {
#ifdef _INFO_
	Serial.println("[INFO] Destroying memory manager ");
#endif
}

bool Memory::loadMemory(int memoryNumber) {
	if (currentMap != memoryNumber) {
#ifdef _INFO_
		Serial.print("[INFO] Switching memory from ");
		Serial.print(currentMap);
		Serial.print(" to ");
		Serial.println(memoryNumber);
#endif
		storeInternal(currentMap);
		loadInternal(memoryNumber);
		currentMap = memoryNumber;
		return true;
	} else {
		return false;
	}
}



StateActions Memory::getStateActions(State* state) {
#ifdef _DEBUG_
	Serial.print("[DEBUG] Get state actions for state: ");Serial.println(state->getStateName());
#endif
	for (int i = 0; i < stateMap.stateCount; i++) {
		if (stateMap.states[i].state == state) {
			return stateMap.states[i];
		}
	}
#ifdef _ERROR_
	Serial.println("[ERROR] No state action found. Wrong configuration");
#endif
}

//StateMap& Memory::getMemory(int memoryNumber){
//	Segment* next = this->firstSegment;
//	while (next->next != 0 && next->memoryNumber!=memoryNumber){
//		next=next->next;
//	}
//
//	if (next->memoryNumber == memoryNumber){
//#ifdef _INFO_
//Serial.print("[INFO] Returning existing memory for: ");Serial.println(memoryNumber);
//#endif
//		return next->states;
//	} else {
//		Segment* created = new Segment;
//		created->memoryNumber=memoryNumber;
//		created->states = firstSegment->states;
//		next->next=created;
//#ifdef _INFO_
//	Serial.print("[INFO] Creating memory for: ");Serial.println(memoryNumber);
//#endif
//	return created->states;
//	}
//}

} /* namespace q_behave */
