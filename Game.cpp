/*
 * Game.cpp
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#include "Game.h"

#include <SDL2/SDL_events.h>

#include "common.h"
#include "Rock.h"
#include "Ship.h"
namespace Space {

Game::Game() {
	addObject(new Ship(this));
	addObject(new Rock(this, 0, 1));
}

Game::~Game() {
}

void Game::render() {
	for(auto it: _objects){
		it->draw();
	}
}

void Game::update(double t) {
	for (auto it: _objects){
		it->update(t);
	}
}

void Game::addObject(IObject* object) {
	_objects.push_back(object);
}

void Game::addCommandListener(ICommandListener* listener) {
	_commandListeners.push_back(listener);
}

void Game::removeCommandListener(ICommandListener* listener) {
	_commandListeners.remove(listener);
}

void Game::updateKeyListeners(ICommandListener::CommandType type, double value) {
	for (auto it : _commandListeners)
	{
		it->sendCommand(type, value);
	}
}


void Space::Game::handleEvent(SDL_Event* event) {
	switch(event->type){
	case SDL_KEYDOWN:
//		debug_print( " %c\n", event->key.keysym.sym);
	{
		auto pressedKey = event->key.keysym.sym;
		switch (pressedKey) {
			case 'a':
			case 'A':
				updateKeyListeners(ICommandListener::Left, 1);
				break;
			case 'd':
			case 'D':
				updateKeyListeners(ICommandListener::Right, 1);
				break;
			case 'w':
			case 'W':
				updateKeyListeners(ICommandListener::Forward, 1);
				break;
			case 's':
			case 'S':
				updateKeyListeners(ICommandListener::Backward, 1);
				break;
			case ' ':
				updateKeyListeners(ICommandListener::Fire, 1);
				break;
			default:
				break;
		}
	}
		break;
	case SDL_KEYUP:

	{
		auto pressedKey = event->key.keysym.sym;
		switch (pressedKey) {
			case 'a':
			case 'A':
				updateKeyListeners(ICommandListener::Left, 0);
				break;
			case 'd':
			case 'D':
				updateKeyListeners(ICommandListener::Right, 0);
				break;
			case 'w':
			case 'W':
				updateKeyListeners(ICommandListener::Forward, 0);
				break;
			case 's':
			case 'S':
				updateKeyListeners(ICommandListener::Backward, 0);
				break;
			case ' ':
				updateKeyListeners(ICommandListener::Fire, 0);
				break;
			default:
				break;
		}
	}
//		debug_print("Key up \n");
		break;
	}
}

} /* namespace Space */
