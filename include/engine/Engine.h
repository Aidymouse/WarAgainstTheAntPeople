#pragma once

#include <engine/StateManager.h>
#include <SDL3/SDL.h>

class Engine {

	SDL_Window *window;
	StateManager state_manager;

public:
	Engine();
	void run();
};
