#pragma once

#include <ecs/ECS.hpp>
#include <engine/CollisionGrid.h>

namespace Spawners {
void add_guy(ECS *ecs, CollisionGrid *grid);
void add_scrap(ECS *ecs);
} // namespace Spawners
