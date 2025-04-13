#pragma once

#include <SDL3/SDL.h>
#include <engine/StateManager.h>

class Engine {

  StateManager state_manager;

public:
  Engine();
  void run();
};
