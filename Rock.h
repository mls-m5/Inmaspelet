/*
 * Rock.h
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#pragma once

#include "Game.h"
#include "Image.h"
#include "IObject.h"

using Images::Image;

namespace Space {

class Rock: public IObject {
public:
	Rock(Game *game, double x, double y);

	virtual ~Rock();

	virtual void draw();

	virtual void update(double t);

private:

	double _posX;
	double _posY;
	double _angle = 0;
	double radius = .3;
	Game *_game;
	Image _image;
};

} /* namespace Space */
