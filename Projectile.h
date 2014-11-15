/*
 * Projectile.h
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#pragma once

#include "IObject.h"

namespace Space {

class Projectile: public IObject {
public:
	Projectile(double x, double y);

	virtual ~Projectile();

	virtual void draw();

	virtual void update(double t);

private:

	double _posX;
	double _posY;
	double _angle = 0;
	double _speed = .1;
};

} /* namespace Space */
