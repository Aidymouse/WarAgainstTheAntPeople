#pragma once

// #include "engine/CollisionGrid.h"
#include <ecs/ECS.hpp>
#include <ecs/System.hpp>
#include <engine/CollisionGrid.h>

class TransformSystem : public System {
public:
  // void update(float dt, CollisionGrid *grid);
  void update(float dt, CollisionGrid *grid, ECS *ecs);
};
