#pragma once

#include <ecs/System.hpp>

class FollowsMouseSystem : public System {

public:
  void update(float dt);
};
