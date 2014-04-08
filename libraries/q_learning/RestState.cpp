/*
 * RestState.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: marek
 */
#ifndef _TEST_
#include <Arduino.h>
#else
#include "mock_arduino.h"
#endif

#include "RestState.h"

namespace q_learning {

RestState::RestState() {

}

RestState::~RestState() {
}

char* RestState::getStateName(){
	return "rest";
}

void RestState::activate(){
	//do nothing
}

void RestState::deactivate(){
	//do nothing
}

} /* namespace q_learning */
