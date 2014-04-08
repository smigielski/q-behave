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

MockState::MockState(char* _stateName,int* _state) {
	this->stateName=_stateName;
	this->state=_state;
}

MockState::~MockState() {

}

char* MockState::getStateName(){
	return this->stateName;
}


void MockState::activate(){
	*state =1;
}

void MockState::deactivate(){
	*state =0;
}

} /* namespace q_learning */
