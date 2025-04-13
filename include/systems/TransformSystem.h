#pragma once

#include "engine/CollisionGrid.h"
#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

class TransformSystem : public System {
public:
  void update(float dt, CollisionGrid *grid);
};
