/*
 * Game.h
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#pragma once
#include <SDL2/SDL_events.h>
#include <list>

#include "ICommandListener.h"
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
	void addCommandListener(ICommandListener *);
	void removeCommandListener(ICommandListener *);

private:
	 void updateKeyListeners(ICommandListener::CommandType type, double value);

	std::list<IObject *> _objects;
	std::list<ICommandListener*> _commandListeners;
};

} /* namespace Space */
