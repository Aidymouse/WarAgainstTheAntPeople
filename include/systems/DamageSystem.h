#pragma once

#include "engine/CollisionGrid.h"
#include <SDL3/SDL.h>
#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

class DamageSystem : public System {
public:
	void update(float dt, ECS *ecs, CollisionGrid *grid);
	void process_post_damage_behaviours(ECS *ecs, CollisionGrid *grid);
};
