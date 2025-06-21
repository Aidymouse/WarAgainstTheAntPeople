#pragma once

#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

class HivemindBrainSystem : public System {
public:
  void update(float dt, ECS *ecs);
};
