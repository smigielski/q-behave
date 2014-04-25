/*
 * State machine with learning capabilities.
 *
 * Copyright (C) 2014 Poliprojekt.pl sp. z o.o.
 * Author: Marek Smigielski <marek.smigielski@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef RESTSTATE_H_
#define RESTSTATE_H_

#include "State.h"

namespace q_behave {

/**
 * State used as a rest state. Activating or deactivating does not have any visible action.
 * It can be used as a start state.
 */
class RestState: public q_behave::State {
public:
	RestState();
	virtual void activate();
	virtual void deactivate();
};

} /* namespace q_behave */

#endif /* RESTSTATE_H_ */
