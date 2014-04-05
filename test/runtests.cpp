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




using namespace q_learning;

RestState restState = RestState();
StateActions states[1];
Action actions[1];
StateMap stateMap;


int main(int argc, char **argv){

	states[0].actionCount=1;
	actions[0].quality=1;
	actions[0].state=&restState;
	states[0].actions=actions;
	states[0].state=&restState;

	stateMap.stateCount=1;
	stateMap.states=states;

	Brain* brain = new Brain(&restState, stateMap);
	brain->start(0);
	delete brain;
}

