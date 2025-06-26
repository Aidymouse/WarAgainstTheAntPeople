

#pragma once

#include "engine/CollisionGrid.h"
#include <SDL3/SDL.h>
#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

class BuildSystem : public System {
public:
  void update(float dt, ECS *ecs, CollisionGrid *grid);
  // void draw(SDL_Renderer *renderer, ECS *ecs);
};
