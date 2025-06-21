
#pragma once

#include <SDL3/SDL.h>
#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

class GeneralCollisionHandlerSystem : public System {
public:
  void update(float dt, ECS *ecs);
};
