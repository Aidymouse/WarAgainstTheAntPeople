#include <engine/Engine.h>
#include <states/MainState.h>

#include <ProjectConfig.h>
#include <SDL3/SDL.h>

/** Basically just the state machine to switch between pause and running */

Engine::Engine() {

	SDL_Init(SDL_INIT_VIDEO);


	state_manager.set_state(std::make_shared<MainState>());
	
	
}

void Engine::run() {
	
	window = SDL_CreateWindow(
		"This Window",
		800,
		600,
SDL_WINDOW_OPENGL
	);

	std::cout << window << std::endl;

	bool window_is_open = true;
	while (window_is_open) {
		//window->height

		//std::shared_ptr<GameState> current_state = state_manager.get_current_state();

		/** Event based */


		/* Update */
		//float dt = clock.restart().asSeconds();
		// float dt = 0.016;
		//
		// current_state->update(dt);

		/* Draw */
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
		    if (event.type == SDL_EVENT_QUIT) {
			window_is_open = false;
		    }
		}

			// Do game logic, present a frame, etc.

	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}
