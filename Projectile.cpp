/*
 * Projectile.cpp
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#include "Projectile.h"

#include <SDL2/SDL_opengl.h>
namespace Space {

Projectile::Projectile(Game *game, double x, double y)
:_posX(x)
,_posY(y)
,_game(game)
{
}

Projectile::~Projectile() {
}

void Projectile::draw() {
	glLoadIdentity();
	glTranslatef(_posX, _posY, 0);
	glScaled(.01,.01,.01);
	glRotated(_angle, 0,0,1);
	glBegin(GL_TRIANGLES);
	glColor3f(1,1,1);
	glVertex2f(0, + 1);
	glVertex2f(- .5,  - 1);
	glVertex2f(+ .5, - 1);
	glEnd();
}

void Projectile::update(double t) {
	_posY += _speed;
}

} /* namespace Space */
