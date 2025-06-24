#pragma once

#include <ecs/Entity.hpp>
#include <util/Vec2.hpp>

#define MAX_ENTITIES_IN_HIVEMIND 10

/** Having this component is what makes something a hivemind */
struct hv_Brain {
  Entity entities[MAX_ENTITIES_IN_HIVEMIND];
  int num_entities;
};

struct hv_Participant {
  Vec2 offset; // Offset from hiveminds position
};
