#pragma once

#include <ecs/ECS.hpp>
#include <engine/CollisionGrid.h>

namespace Spawners {
void add_guy(ECS *ecs, CollisionGrid *grid);
void add_scrap(ECS *ecs, CollisionGrid *grid);
void shoot_rock(ECS *ecs, CollisionGrid *grid, Vec2 pos, Vec2 dir);
} // namespace Spawners
