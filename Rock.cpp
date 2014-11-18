/*
 * Rock.cpp
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#include "Rock.h"

#include <GL/gl.h>
namespace Space {

Rock::Rock(Game *game, double x, double y)
: _posX(x)
, _posY(y)
, _game(game)
, _image("data/Rock.png")
{
}

Rock::~Rock() {
}

void Rock::draw() {
	_image.draw(_posX, _posY, _angle, radius, radius, 1);
}

void Rock::update(double t) {
	_posY -= .01;
}

} /* namespace Space */
