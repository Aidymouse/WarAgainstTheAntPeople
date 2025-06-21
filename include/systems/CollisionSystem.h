#pragma once

#include "engine/CollisionGrid.h"
#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

class CollisionSystem : public System {
public:
  void update(float dt, ECS *ecs, CollisionGrid *grid);
  void strip_collided(float dt, ECS *ecs);
};
