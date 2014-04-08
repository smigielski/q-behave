/*
 * State.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: marek
 */
#ifndef _TEST_
#include <Arduino.h>
#else
#include "mock_arduino.h"
#endif

#include "State.h"

namespace q_learning {

State::State() {

}

State::~State() {

}

State* State::switchTo(State* state){
#ifdef _INFO_
	Serial.print("[INFO] switch from state ");Serial.print(this->getStateName());Serial.print(" to state ");Serial.println(state->getStateName());
#endif
	if (this!=state){
		this->deactivate();
		state->activate();
	}
	return state;
}

} /* namespace q_learning */
