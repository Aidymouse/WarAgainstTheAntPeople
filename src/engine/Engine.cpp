#include <engine/Engine.h>
#include <states/MainState.h>

#include <data/TextureStore.hpp>

#include <ProjectConfig.h>
#include <SDL3/SDL.h>

/** Basically just the state machine to switch between pause and running */

Engine::Engine() { SDL_Init(SDL_INIT_VIDEO); }

void Engine::run() {

  SDL_Window *window = SDL_CreateWindow("This Window", 800, 600, 0);
  SDL_Renderer *main_renderer = SDL_CreateRenderer(window, NULL);

  float now = SDL_GetPerformanceCounter();
  float last = 0;
  float dt = 0;

  TextureStore &texture_store = TextureStore::getInstance();
  // store.p();
  /** Load Textures */
  texture_store.load_texture(std::string(GRAPHICS_PATH).append("guy_sheet.bmp"),
                             "guy_sheet", main_renderer);
  texture_store.load_texture(std::string(GRAPHICS_PATH).append("scrap.bmp"),
                             "scrap_sheet", main_renderer);

  // Load Main State
  state_manager.set_state(std::make_shared<MainState>());
  std::shared_ptr<GameState> cur_state = state_manager.get_current_state();

  bool window_is_open = true;
  while (window_is_open) {

    /** Event based */
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        window_is_open = false;
      }
    }

    /* Update */

    // Update DeltaTime
    last = now;
    now = SDL_GetPerformanceCounter();
    dt = (now - last * 1000) / SDL_GetPerformanceFrequency();

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
