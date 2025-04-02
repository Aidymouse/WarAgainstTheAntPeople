#pragma once

#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

// Handles entities looking for other entities
class ScanningSystem : public System {
public:
  void update(float dt, ECS *ecs);
};
