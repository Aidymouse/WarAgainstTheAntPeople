#pragma once

#include "engine/CollisionGrid.h"
#include <components/GuyComponents.hpp>
#include <ecs/ECS.hpp>

namespace GuySM {
//
// Helpers to enter / exit states by manipulating components
g_Wandering *enter_wandering(Entity guy_id, ECS *main_ecs);
void enter_seeking(Entity guy_id, ECS *main_ecs);
void die(Entity guy_id, ECS *main_ecs, CollisionGrid *grid);
} // namespace GuySM
