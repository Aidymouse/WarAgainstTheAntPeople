#include "engine/Components.hpp"
#include <systems/CollisionHandlerSystem.h>

void CollisionHandlerSystem::update(float dt, ECS *ecs) {

  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {

    Entity ent = (Entity)*e;

    Collider col = *component_manager->get_component_data<Collider>(ent);
  }
}
