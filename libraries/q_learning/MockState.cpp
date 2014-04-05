/*
 * MockState.cpp
 *
 *  Created on: Apr 5, 2014
 *      Author: marek
 */
#ifndef _TEST_
#include <Arduino.h>
#else
#include "mock_arduino.h"
#endif

#include "MockState.h"

namespace q_learning {

MockState::MockState(char* _stateName) {
	this->stateName=_stateName;
}

MockState::~MockState() {
	// TODO Auto-generated destructor stub
}

char* MockState::getStateName(){
	return this->stateName;
}

State* MockState::switchTo(State* state){
#ifdef _INFO_
	char myConcatenation[80];
	sprintf(myConcatenation,"[INFO] switch from state %s to state %s ",this->getStateName(),state->getStateName());
	Serial.write(myConcatenation);
#endif
	if (this!=state){
		this->deactivate();
		state->activate();
	}
	return state;
}

void MockState::activate(){
	//do nothing
}

void MockState::deactivate(){
	//do nothing
}

} /* namespace q_learning */
