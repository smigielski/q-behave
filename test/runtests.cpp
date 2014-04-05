/*
 DSM2_tx implements the serial communication protocol used for operating
 the RF modules that can be found in many DSM2-compatible transmitters.

 Copyrigt (C) 2012  Erik Elmore <erik@ironsavior.net>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mock_arduino.h"
#include "../libraries/q_learning/Brain.h"
#include "../libraries/q_learning/RestState.h"
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

int main(int argc, char **argv) {
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
	//TODO check that it was learned
	//learn mock1
	int success2=0;
	int count2 = 0;
	while (success2<5&&count2<1000) {
		brain.start(0);
		count2++;
		if (brain.currentState == &mock1) {
			brain.stop(10.0);
			success2++;
		} else {
			brain.stop(-10.0);
			success2=0;
		}
	}
#ifdef _INFO_
	char myConcatenation[80];
	sprintf(myConcatenation,"[INFO] Mock2 count: %i, success: %i",count1,success1);
	Serial.write(myConcatenation);
	sprintf(myConcatenation,"[INFO] Mock1 count: %i, success: %i",count2,success2);
	Serial.write(myConcatenation);
#endif

}
