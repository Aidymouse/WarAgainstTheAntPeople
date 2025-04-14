#pragma once

#include <ecs/System.hpp>
#include <ecs/ECS.hpp>
#include <engine/CollisionGrid.h>

class FollowsMouseSystem : public System {

public:
  void update(float dt, ECS *ecs, CollisionGrid *grid);
};
