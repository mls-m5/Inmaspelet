/*
 * Rock.cpp
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#include "Rock.h"

#include <SDL2/SDL_opengl.h>
namespace Space {

Rock::Rock(Game *game, double x, double y)
:_posX(x)
,_posY(y)
,_game(game)
{
}

Rock::~Rock() {
}

void Rock::draw() {
	glLoadIdentity();
	glTranslatef(_posX, _posY, 0);
	glScaled(radius, radius, radius);
	glRotated(_angle, 0,0,1);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,1,1);
	glVertex2f(0, + 1);
	glVertex2f(- 1,  0);
	glVertex2f(0, - 1);
	glVertex2f(- 1, 0);
	glEnd();
}

void Rock::update(double t) {
	_posY -= .01;
}

} /* namespace Space */
