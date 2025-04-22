#pragma once

#include <SDL3/SDL.h>
#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

class DrawSystem : public System {
public:
  void update(float dt, ECS *ecs);
  void draw(SDL_Renderer *renderer, ECS *ecs, int num_reserved);
};
