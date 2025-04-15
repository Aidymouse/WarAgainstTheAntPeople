#pragma once

#include "SDL3/SDL_events.h"
#include <SDL3/SDL.h>

class GameState {
public:
  virtual void update(float dt) = 0;
  virtual void draw(SDL_Renderer *renderer) = 0;

  virtual void handle_click(SDL_Event *event) {};
  virtual void handle_mousemove() {};

  virtual void leave_state() = 0;
  virtual void enter_state() = 0;
};
