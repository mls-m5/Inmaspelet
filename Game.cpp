/*
 * Game.cpp
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#include "Game.h"

#include <SDL2/SDL_events.h>

#include "common.h"
#include "Ship.h"
namespace Space {

Game::Game() {
	addObject(new Ship(this));
}

Game::~Game() {
}

void Game::render() {
	for(auto it: _objects){
		it->draw();
	}
}

void Game::update(double t) {
}

void Game::addObject(IObject* object) {
	_objects.push_back(object);
}

} /* namespace Space */

void Space::Game::handleEvent(SDL_Event* event) {
	switch(event->type){
	case SDL_KEYDOWN:
		debug_print( " %c\n", event->key.keysym.sym);
		break;
	case SDL_KEYUP:
		debug_print("Key up \n");
		break;
	}
}
