#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include <engine/Engine.h>
#include <states/MainState.h>

#include <data/TextureStore.hpp>
#include <data/AnimStore.hpp>

#include <ProjectConfig.h>
#include <SDL3/SDL.h>

/** Basically just the state machine to switch between pause and running */

void load_textures(SDL_Renderer *renderer) {
  TextureStore &texture_store = TextureStore::getInstance();

  texture_store.load_texture(std::string(GRAPHICS_PATH).append("guy_sheet.bmp"), "guy_sheet", renderer);
  texture_store.load_texture(std::string(GRAPHICS_PATH).append("scrap.bmp"), "scrap_sheet", renderer);
  texture_store.load_texture(std::string(GRAPHICS_PATH).append("squish.bmp"), "squish_sheet", renderer);
  texture_store.load_texture(std::string(GRAPHICS_PATH).append("hand_sheet.bmp"), "tool_hand", renderer);
  texture_store.load_texture(std::string(GRAPHICS_PATH).append("tower.bmp"), "tower", renderer);
  texture_store.load_texture(std::string(GRAPHICS_PATH).append("rock.bmp"), "rock", renderer);
  texture_store.load_texture(std::string(GRAPHICS_PATH).append("cannon.bmp"), "cannon", renderer);
}

void load_animations() {
  	AnimStore &anim_store = AnimStore::getInstance();

	// Guy
	anim_store.load_animation("guy_norm1", "guy_sheet", {0, 0, 16, 16}, 0.1, {7, 11});
	anim_store.load_animation("guy_norm2", "guy_sheet", {16, 0, 16, 16}, 0.1, {7, 11});
	anim_store.set_next_animation("guy_norm1", "guy_norm2");
	anim_store.set_next_animation("guy_norm2", "guy_norm1");

	// Guy Squish
	anim_store.load_animation("guy_squish0", "squish_sheet", {0, 0, 16, 16}, 0.035, {7, 11});
	anim_store.load_animation("guy_squish1", "squish_sheet", {1*16, 0, 16, 16}, 0.035, {7, 11});
	anim_store.set_next_animation("guy_squish0", "guy_squish1");
	anim_store.load_animation("guy_squish2", "squish_sheet", {2*16, 0, 16, 16}, 0.035, {7, 11});
	anim_store.set_next_animation("guy_squish1", "guy_squish2");
	anim_store.load_animation("guy_squish3", "squish_sheet", {3*16, 0, 16, 16}, 0.035, {7, 11});
	anim_store.set_next_animation("guy_squish2", "guy_squish3");
	anim_store.load_animation("guy_squish4", "squish_sheet", {4*16, 0, 16, 16}, 0.035, {7, 11});
	anim_store.set_next_animation("guy_squish3", "guy_squish4");
	anim_store.load_animation("guy_squish5", "squish_sheet", {5*16, 0, 16, 16}, 0.035, {7, 11});
	anim_store.set_next_animation("guy_squish4", "guy_squish5");
	anim_store.load_animation("guy_squish6", "squish_sheet", {6*16, 0, 16, 16}, -1, {7, 11});
	anim_store.set_next_animation("guy_squish5", "guy_squish6");

	// Single frames for stuff that dont move
	anim_store.load_animation("scrap", "scrap_sheet", {16, 0, 16, 16}, -1, {8, 8});
	anim_store.load_animation("tower", "tower", {3*32, 0, 32, 64}, -1, {16, 64});
	anim_store.load_animation("rock", "rock", {0, 0, 8, 8}, -1, {8, 8});
	anim_store.load_animation("cannon", "cannon", {0, 0, 32, 32}, -1, {16, 16});

	// Tools
	anim_store.load_animation("tool_hand_norm", "tool_hand", {32, 0, 32, 32}, -1, {16, 16});

	// Build sites
	anim_store.load_animation("build_tower1", "tower", {0, 0, 32, 64}, -1, {16, 64});
	anim_store.load_animation("build_tower2", "tower", {1*32, 0, 32, 64}, -1, {16, 64});
	anim_store.load_animation("build_tower3", "tower", {2*32, 0, 32, 64}, -1, {16, 64});

}

Engine::Engine() { SDL_Init(SDL_INIT_VIDEO); }

void Engine::run() {

	TextureStore &texture_store = TextureStore::getInstance();

	SDL_Window *window = SDL_CreateWindow("The Evil Pikmin...", 800, 600, 0);
	SDL_Renderer *main_renderer = SDL_CreateRenderer(window, NULL);
	SDL_SetRenderDrawBlendMode(main_renderer, SDL_BLENDMODE_BLEND);

	float now = SDL_GetPerformanceCounter();
	float last = 0;
	float dt = 0;

	/** Load Textures */
	load_textures(main_renderer);
	load_animations();

	// Load Main State
	state_manager.set_state(std::make_shared<MainState>());
	std::shared_ptr<GameState> cur_state = state_manager.get_current_state();

	bool window_is_open = true;
	float fps_timer = 0;
	float frames = 0;
	while (window_is_open) {

		/** Event based */
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				window_is_open = false;
			} else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				cur_state->handle_click(&event);
			} else if (event.type == SDL_EVENT_KEY_DOWN) {
				cur_state->handle_keydown(&event);
			}
		}

		/* Update */

		// Update DeltaTime
		last = now;
		now = SDL_GetPerformanceCounter();
		dt = ((now - last)) / SDL_GetPerformanceFrequency();
		frames++;
		fps_timer += dt;
		if (fps_timer > 1) {
		 	//std::cout << "FPS: " << frames << std::endl;
			fps_timer -= 1;
			frames = 0;
		}

		cur_state->update(dt);

		/* Draw */
		SDL_SetRenderDrawColor(main_renderer, 255, 255, 255, 255);
		SDL_RenderClear(main_renderer);

		// cur_state->draw(main_renderer);

		// Texture ?
		SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255);

		cur_state->draw(main_renderer);

		SDL_RenderPresent(main_renderer);
	}

	texture_store.destroy_textures();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(main_renderer);

	// SDL_DestroySurface(guysurface);

	SDL_Quit();
}
