/*
 * Ship.h
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#pragma once

#include "Game.h"
#include "ICommandListener.h"
#include "IObject.h"

namespace Space {

class Game;

class Ship: public IObject, ICommandListener {
public:
	Ship(Game *game);

	virtual void draw();

	virtual void update(double t);

	virtual ~Ship();

	virtual void sendCommand(CommandType type, double value);

private:
	double _posX = 0;
	double _posY = 0;
	double _heading = 0;

	// Todo add images.

	Game *_game;
};


} /* namespace Space */
