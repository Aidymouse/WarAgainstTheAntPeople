
#pragma once

#include <SDL3/SDL.h>
#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

class CarrySystem : public System {
public:
  void update(float dt, ECS *ecs);
  // void draw(SDL_Renderer *renderer, ECS *ecs);
};
