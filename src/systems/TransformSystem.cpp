#include "engine/Components.hpp"
#include <systems/TransformSystem.h>

void TransformSystem::update(float dt) {

  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {
    Entity ent = (Entity)*e;
    Position *pos = component_manager->get_component_data<Position>(ent);
    Transform *trans = component_manager->get_component_data<Transform>(ent);

    pos->x += trans->vel_x * dt;
    pos->y += trans->vel_y * dt;
    pos->z += trans->vel_z * dt;

    // grid->update_entity(ent, *pos);

    // If we were gonna do acceleration or anything we do it here
  }
};
