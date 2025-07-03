#pragma once

#include <ecs/ECS.hpp>

void stop_being_carryable(ECS *ecs, Entity ent);
void advance_build_stage(ECS *ecs, Buildable *b, Entity ent);
