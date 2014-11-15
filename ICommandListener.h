/*
 * IEventListener.h
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#pragma once

namespace Space {

class ICommandListener {
public:
	enum CommandType {
		Left,
		Right,
		Forward,
		Backward,
		Fire,
	};
	virtual ~ICommandListener() {};

	virtual void sendCommand(CommandType type, double value) = 0;
};

} /* namespace Space */
