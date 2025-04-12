#include <engine/Engine.h>
#include <states/MainState.h>

#include <ProjectConfig.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>

/** Basically just the state machine to switch between pause and running */

Engine::Engine() {

  SDL_Init(SDL_INIT_VIDEO);

  state_manager.set_state(std::make_shared<MainState>());
}

void Engine::run() {

  window = SDL_CreateWindow("This Window", 800, 600, SDL_WINDOW_OPENGL);
  SDL_Renderer *renderer;

  // SDL_CreateWindowAndRenderer("This Winto", 800, 600, SDL_WINDOW_OPENGL,
  //                             &window, &renderer);

  SDL_GLContext ctx = SDL_GL_CreateContext(window);
  std::cout << window << std::endl;

  // ctx.glClear(0, 0, 0, 1);
  // glClearColor(0, 0, 0, 1); // TODO: why this doesn't work???
  // glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(window);
  bool window_is_open = true;
  while (window_is_open) {
    // window->height

    // std::shared_ptr<GameState> current_state =
    // state_manager.get_current_state();

    /** Event based */
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        window_is_open = false;
      }
    }

    /* Update */
    // float dt = clock.restart().asSeconds();
    //  float dt = 0.016;
    //
    //  current_state->update(dt);

    /* Draw */

    // SDL_RenderClear(renderer);
    // SDL_RenderPresent(renderer);
  }

  SDL_DestroyWindow(window);
  SDL_GL_DestroyContext(ctx);
  SDL_Quit();
}
