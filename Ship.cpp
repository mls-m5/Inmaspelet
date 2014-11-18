/*
 * Ship.cpp
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#include "Ship.h"

#include <GL/gl.h>

#include "common.h"
#include "Projectile.h"

namespace Space {

Ship::Ship(Game* game)
: _game(game)
, _image("data/SpaceShip.png")
{
	game->addCommandListener(this);
}


void Ship::draw() {
	_image.draw(_posX, _posY, _heading, 1, 1, .5);
}

void Ship::update(double t) {
	_posX += _commands[ICommandListener::Left] * speed;
	_posX -= _commands[ICommandListener::Right] * speed;
	_posY += _commands[ICommandListener::Forward] * speed;
	_posY -= _commands[ICommandListener::Backward] * speed;

	_posX = min(_posX, 1.);
	_posX = max(_posX, -1.);

	_posY = min(_posY, 1.);
	_posY = max(_posY, -1.);

	if (_commands[ICommandListener::Fire]) {
		_game->addObject(new Projectile(_game, _posX, _posY));
	}
}
Ship::~Ship() {
	if (_game) {
		_game->removeCommandListener(this);
	}
}

void Ship::sendCommand(CommandType type, double value) {
	_commands[type] = value;
}

} /* namespace Space */
