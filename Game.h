/*
 * Game.h
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#pragma once
#include <SDL2/SDL_events.h>
#include <list>

#include "IObject.h"
namespace Space {

class Game {
public:
	Game();
	virtual ~Game();

	void render();
	void update(double t);
	void addObject(IObject *object);
	void handleEvent(SDL_Event *event);

private:
	std::list<IObject *> _objects;
};

} /* namespace Space */
