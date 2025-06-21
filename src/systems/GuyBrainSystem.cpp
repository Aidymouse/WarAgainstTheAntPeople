// System that handles making decisions for a guy. The only thing we know for
// sure is that we have a guy present. This is, like, probably against ECS ethos
// or some shit.
//
#include "ai/GuyAI.h"
#include "components/Components.hpp"
#include <components/GuyComponents.hpp>
#include <ecs/ECS.hpp>
#include <systems/GuyBrainSystem.h>

void GuyBrainSystem::update(float dt, ECS *ecs) {
  /** Decision Making */
  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {

    Entity ent = (Entity)*e;
    // Basically just like... subsystems ??
  }

  /** Wandering */
  std::shared_ptr<ComponentArray<g_Wandering>> comp_wandering =
      ecs->get_component_array<g_Wandering>();

  for (int i = 0; i < comp_wandering->get_num_components(); i++) {
    Entity e = comp_wandering->get_entity_from_idx(i);

    g_Wandering *wander_data = comp_wandering->get_editable_data(e);
    Transform *t = ecs->get_component_for_entity<Transform>(e);

    wander_data->timer -= dt;
    t->vel_x = wander_data->dir.x * wander_data->speed;
    t->vel_y = wander_data->dir.y * wander_data->speed;

    if (wander_data->timer < 0) {
      int angle = rand() % 360;
      int speed = 20 + rand() % 30; // 20 - 50
      Vec2 dir = Vec2(1, 0);
      dir.face_angle(angle);
      float timer = (2 + rand() % 10) / 2.f;

      wander_data->dir = dir;
      wander_data->speed = speed;
      wander_data->timer = timer;
    }
  }
}
