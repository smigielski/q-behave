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

Memory::Memory(StateMap _stateMap,double* _internalMemmory[]) {
	this->stateMap = _stateMap;
	this->internalMemmory=_internalMemmory;
	currentMap=0;
}

Memory::~Memory() {
#ifdef _INFO_
	Serial.println("[INFO] Destroying memory manager ");
#endif
}

bool Memory::loadMemory(int memoryNumber) {
	if (currentMap!=memoryNumber){
#ifdef _INFO_
	Serial.print("[INFO] Switching memory from ");
	Serial.print(currentMap);
	Serial.print(" to ");
	Serial.println(memoryNumber);
#endif
		storeInternal(currentMap);
		loadInternal(memoryNumber);
		currentMap=memoryNumber;
		return true;
	} else {
		return false;
	}
}

void Memory::storeInternal(int memoryNumber){
	int position = 0;
	for (int i = 0; i < stateMap.stateCount; i++) {
		for (int j =0; j< stateMap.states[i].actionCount; j++){
			internalMemmory[memoryNumber][position++]=stateMap.states[i].actions[j].quality;
		}
	}
}

void Memory::loadInternal(int memoryNumber){
	int position = 0;
	for (int i = 0; i < stateMap.stateCount; i++) {
		for (int j =0; j< stateMap.states[i].actionCount; j++){
			stateMap.states[i].actions[j].quality=internalMemmory[memoryNumber][position++];
		}
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

} /* namespace q_learning */
