
#include <ctime>
#include <iostream>

#include <engine/Engine.h>
#include <ProjectConfig.h>


int main() {

	// std::cout << "Graphics Path: " << GRAPHICS_PATH << std::endl;
	//
	// srand(time(NULL));
	//
	// Engine game;
	// game.run();
	
	SDL_Window *window = SDL_CreateWindow("Winto", 800, 600, SDL_WINDOW_OPENGL);

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
	


}
