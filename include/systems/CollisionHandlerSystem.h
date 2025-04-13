#pragma once

#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

class CollisionHandlerSystem : public System {
public:
  void update(float dt, ECS *ecs);
};
