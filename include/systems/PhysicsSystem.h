#pragma once

#include <ecs/System.hpp>

class PhysicsSystem : public System {
public:
	void update(float dt);
};

