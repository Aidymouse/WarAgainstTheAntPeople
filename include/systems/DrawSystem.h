#pragma once

#include <ECS/System.hpp>
#include <SDL3/SDL.h>

class DrawSystem : public System {
public:
  void update(float dt, ECS *ecs);
  void draw(SDL_Renderer *renderer);
};
