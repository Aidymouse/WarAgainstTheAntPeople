#pragma once

#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

class GuyBrainSystem : public System {
public:
  void update(float dt, ECS *ecs);
  void g_handle_collisions(float dt, ECS *ecs);
};
