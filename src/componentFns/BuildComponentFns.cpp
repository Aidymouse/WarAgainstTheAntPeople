#include "components/Components.hpp"
#include <componentFns/BuildComponentFns.h>

void stop_being_carryable(ECS *ecs, Entity ent) {
  Carryable *c = ecs->get_component_for_entity<Carryable>(ent);

  for (int ci = c->carriers_count - 1; ci > 0; ci++) {
  }
}

void create_buildsite(ECS *ecs) {}
