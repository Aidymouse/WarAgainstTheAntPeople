#pragma once

#include "engine/CollisionGrid.h"
#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

class HivemindBrainSystem : public System {
public:
  void update(float dt, ECS *ecs, CollisionGrid *grid);
};
