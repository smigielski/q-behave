// Do not remove the include below
#define _DEBUG_
#define _INfO_

#include "q_learning.h"
#include "./libraries/q_learning/Brain.h"
#include "./libraries/q_learning/RestState.h"
#include "../libraries/q_learning/MockState.h"

using namespace q_learning;

RestState restState = RestState();
MockState mock1 = MockState("mock1");
MockState mock2 = MockState("mock2");

Action restActions[] = { { &mock1, 0.0 }, { &mock2, 0.0 } };
Action mock1Actions[] = { { &mock1, 0.0 }};
Action mock2Actions[] = {  { &mock2, 0.0 } };

StateActions states[3] = {
		{&restState,2, restActions },
		{&mock1,1,mock1Actions},
		{&mock2,1,mock2Actions}
};
StateMap stateMap = { 3, states };

int led = 9;
//The setup function is called once at startup of the sketch
void setup()
{
	  pinMode(led, OUTPUT);
	Brain brain = Brain(&restState, stateMap);
	//learn mock2
	int success1=0;
	int count1 = 0;
	while (success1<5&&count1<1000) {
		brain.start(0);
		count1++;
		if (brain.currentState == &mock2) {
			brain.stop(10.0);
			success1++;
		} else {
			brain.stop(-10.0);
			success1=0;
		}
	}
}

// The loop function is called in an endless loop
void loop()
{
	 digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
	  delay(1000);               // wait for a second
	  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
	  delay(1000);
}
