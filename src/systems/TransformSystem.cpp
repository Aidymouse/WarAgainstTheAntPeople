#include "engine/CollisionGrid.h"
#include "engine/Components.hpp"
#include <systems/TransformSystem.h>

void TransformSystem::update(float dt, CollisionGrid *grid, ECS *ecs) {

  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {
    Entity ent = (Entity)*e;
    Position *pos = component_manager->get_component_data<Position>(ent);
    Transform *trans = component_manager->get_component_data<Transform>(ent);

    pos->x += trans->vel_x * dt;
    pos->y += trans->vel_y * dt;
    pos->z += trans->vel_z * dt;

    if (ecs->get_signature_for_entity(ent)[COMP_SIG::COLLIDER] == 1) {
      Collider *c = component_manager->get_component_data<Collider>(ent);
      // std::cout << "Collider for " << ent << ", " << c << std::endl;

      grid->update_entity(ent, *pos, *c);
    }
    // grid->update_entity(ent, *pos);

    // If we were gonna do acceleration or anything we do it here
  }
};
