/*
 * Memory.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: marek
 */
#ifndef _TEST_
#include <Arduino.h>
#else
#include "mock_arduino.h"
#endif

#include "Memory.h"

namespace q_learning {

Memory::Memory(StateMap main) {
	this->firstSegment = new Segment;
	this->firstSegment->memoryNumber=0;
	this->firstSegment->states=main;
	this->firstSegment->next=0;
}

Memory::~Memory() {
#ifdef _INFO_
	Serial.print("[INFO] Destroying memory manager ");
#endif
	Segment* next = this->firstSegment;
	while (next != 0){
		Segment* current = next;
		next=next->next;
		delete current;
	}
}

StateActions Memory::getStateActions(State* state) {
#ifdef _DEBUG_
	Serial.print("[DEBUG] Get state actions for state: ");Serial.println(state->getStateName());
#endif
	for (int i = 0; i < memory.stateCount; i++) {
		if (memory.states[i].state == state) {
			return memory.states[i];
		}
	}
#ifdef _ERROR_
	Serial.println("[ERROR] No state action found. Wrong configuration");
#endif
}

StateMap& Memory::getMemory(int memoryNumber){
	Segment* next = this->firstSegment;
	while (next->next != 0 && next->memoryNumber!=memoryNumber){
		next=next->next;
	}

	if (next->memoryNumber == memoryNumber){
#ifdef _INFO_
Serial.print("[INFO] Returning existing memory for: ");Serial.println(memoryNumber);
#endif
		return next->states;
	} else {
		Segment* created = new Segment;
		created->memoryNumber=memoryNumber;
		created->states = firstSegment->states;
		next->next=created;
#ifdef _INFO_
	Serial.print("[INFO] Creating memory for: ");Serial.println(memoryNumber);
#endif
	return created->states;
	}
}

} /* namespace q_learning */
