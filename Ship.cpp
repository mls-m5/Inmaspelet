/*
 * Ship.cpp
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#include "Ship.h"

#include <GL/gl.h>
namespace Space {

Ship::Ship(Game* game)
 : _game(game)
{

}

void Ship::draw() {
	glLoadIdentity();
	glScaled(.1,.1,.1);
	glTranslatef(_posX, _posY, 0);
	glRotated(_heading, 0,0,1);
	glBegin(GL_TRIANGLES);
	glColor3f(1,1,1);
	glVertex2f(0, + 1);
	glVertex2f(- .5,  - 1);
	glVertex2f(+ .5, - 1);
	glEnd();
}

void Ship::update(double t) {
	_heading += 1;
}

Ship::~Ship() {
	// TODO Auto-generated destructor stub
}

void Ship::sendCommand(CommandType type, double value) {
	if (type == ICommandListener::Left);
}

} /* namespace Space */
