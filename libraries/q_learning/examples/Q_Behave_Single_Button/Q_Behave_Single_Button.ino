/*
  Q-Behave RGB Led Example
  
  Learning Arduino how to behave by pressing buttons and giving rewards. In 
  this example RGB diode is connected to three pins and you can teach 
  Arduino to react with different color for any of three buttons that 
  are connected. 
 
  Reward button is provided to help Arduino learn.
  
  This example code is in the public domain.
*/
 
//Button library created by Alexander Brevig
//https://github.com/tigoe/Button
#include <Button.h>

//Timer library for making rewards (already included)
//http://playground.arduino.cc/Code/SimpleTimer
#include <SimpleTimer.h>

//Internal learning system libraries
#include <QLearningMachine.h>
#include <SimpleMemory.h>

//States
#include <RestState.h>
#include <LedState.h>


using namespace q_learning;

//Define states and buttons
RestState restState = RestState();
LedState green = LedState("green",9);
LedState blue = LedState("blue",10);
LedState red = LedState("red",11);

Button button1 = Button(14);
SimpleTimer rewardTimer;
int timerId;

//Prepare connection map between states. Note that it is allow only to move
//from rest state to led states.
Action restActions[] = { { &green, 0.0 }, { &blue, 0.0 },{ &red, 0.0 } };
Action greenActions[] = { { &restState, 0.0 }, { &blue, 0.0 },{ &red, 0.0 } };
Action blueActions[] = { { &green, 0.0 }, { &restState, 0.0 },{ &red, 0.0 }};
Action redActions[] = { { &green, 0.0 }, { &blue, 0.0 },{ &restState, 0.0 }};

StateActions states[] = {
		{&restState,3, restActions },
		{&green,3,greenActions},
		{&blue,3,blueActions},
                {&red,3,redActions}
};
StateMap stateMap = { 4, states };

//Simple memory definition and configuration. All memory is blocked in heap.
//Please note that memory is volatile right now and will not survive restart.
double prob1[12];
double* internalMemmory[]={prob1};
SimpleMemory memory = SimpleMemory(stateMap,internalMemmory);

//Main learning process. 
QLearningMachine brain = QLearningMachine(&memory,&restState);


//Button configuration
void onReward(){
    Serial.println("onReward: ");
    brain.stop(10.0);
}

void onButton1(Button& b){
    Serial.print("onButton1: ");
    Serial.println(b.pin);
    brain.start(0);
    if (rewardTimer.isEnabled(timerId)){
      //if timer was already enable than restart it
      rewardTimer.restartTimer(timerId);
    } else {
      timerId = rewardTimer.setTimeout(5000, onReward);  
    }
    // will print out "onPress: 12"
}


//Startup code
void setup() {
   Serial.begin(9600);
   button1.pressHandler(onButton1);
}

// the loop routine runs over and over again forever:
void loop() {
  button1.process();
  rewardTimer.run();
}
