/*
  Q-Behave RGB Led Example
  
  Learning Arduino how to behave by pressing buttons and giving rewards. In 
  this example RGB diode is connected to three pins and you can teach 
  Arduino to react with different color for any of three buttons that 
  are connected. 
 
  Reward button is provided to help Arduino learn.
  
  This example code is in the public domain.
*/
 


//Internal learning system libraries
#include <QLearningMachine.h>
#include <SimpleMemory.h>

//States
#include <RestState.h>
#include <LedState.h>

//Interaction
#include <SimpleButton.h>

using namespace q_behave;

//Define states and buttons
RestState restState = RestState();
LedState green = LedState("green",9);
LedState blue = LedState("blue",10);
LedState red = LedState("red",11);

SimpleButton button1 = SimpleButton(14);
SimpleButton button2 = SimpleButton(15);
SimpleButton button3 = SimpleButton(16);
SimpleButton reward = SimpleButton(17);


//Prepare connection map between states. Note that it is allow only to move
//from rest state to led states.
Action restActions[] = { { &green, 0.0 }, { &blue, 0.0 },{ &red, 0.0 } };
Action greenActions[] = { { &restState, 0.0 }};
Action blueActions[] = { { &restState, 0.0 }};
Action redActions[] = { { &restState, 0.0 }};

StateActions states[] = {
		{&restState,3, restActions },
		{&green,1,greenActions},
		{&blue,1,blueActions},
                {&red,1,redActions}
};
StateMap stateMap = { 4, states };

//Simple memory definition and configuration. All memory is blocked in heap.
//Please note that memory is volatile right now and will not survive restart.
double prob1[6],prob2[6],prob3[6];
double* internalMemmory[]={prob1,prob2,prob3};
SimpleMemory memory = SimpleMemory(stateMap,internalMemmory);

//Main learning process. 
QLearningMachine brain = QLearningMachine(&memory,&restState);


//Button configuration
void onReward(SimpleButton& b){
    Serial.print("onReward: ");
    Serial.println(b.pin);
    brain.stop(10.0);
    // will print out "onPress: 12"
}

void onButton1(SimpleButton& b){
    Serial.print("onButton1: ");
    Serial.println(b.pin);
    brain.start(0);
    // will print out "onPress: 12"
}

void onButton2(SimpleButton& b){
    Serial.print("onButton2: ");
    Serial.println(b.pin);
    brain.start(1);
    // will print out "onPress: 12"
}

void onButton3(SimpleButton& b){
    Serial.print("onButton3: ");
    Serial.println(b.pin);
    brain.start(2);
    // will print out "onPress: 12"
}

//Startup code
void setup() {
   Serial.begin(9600);
   
   button1.pressHandler(onButton1);
   button2.pressHandler(onButton2);
   button3.pressHandler(onButton3);
   reward.pressHandler(onReward);
}

// the loop routine runs over and over again forever:
void loop() {
  reward.process();
  button1.process();
  button2.process();
  button3.process();
}
