#pragma once

#include <ecs/ECS.hpp>

namespace GuyAI {
//
// Helpers to enter / exit states by manipulating components
void enter_wandering(Entity guy_id, ECS *main_ecs);
void enter_seeking(Entity guy_id, ECS *main_ecs);
} // namespace GuyAI
