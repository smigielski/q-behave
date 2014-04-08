/*
 * LedState.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: marek
 */
#ifndef _TEST_
#include <Arduino.h>
#else
#include "mock_arduino.h"
#endif

#include "LedState.h"

namespace q_learning {

LedState::LedState(char* _stateName,int _pin) {
	this->stateName=_stateName;
	this->pin=_pin;
	pinMode(pin, OUTPUT);
}

LedState::~LedState() {
}

char* LedState::getStateName(){
	return this->stateName;
}


void LedState::activate(){
	digitalWrite(pin, HIGH);
}

void LedState::deactivate(){
	digitalWrite(pin, LOW);
}

} /* namespace q_learning */
