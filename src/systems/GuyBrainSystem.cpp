// System that handles making decisions for a guy. The only thing we know for
// sure is that we have a guy present. This is, like, probably against ECS ethos
// or some shit.
//
#include "components/Collisions.hpp"
#include "components/Components.hpp"
#include "state_machines/GuySM.h"
#include "util/Random.h"
#include <ProjectConfig.h>
#include <components/GuyComponents.hpp>
#include <ecs/ECS.hpp>
#include <systems/GuyBrainSystem.h>

#include <anim/GuyAnim.hpp>
#include <data/TextureStore.hpp>
#include <engine/CollisionGrid.h>

void gs_wander(float dt, ECS *ecs);
void g_handle_collisions(float dt, ECS *ecs);

const bool guy_brain_debug = false;

TextureStore &gbs_ts = TextureStore::getInstance();

void GuyBrainSystem::update(float dt, ECS *ecs, CollisionGrid *grid) {
  /** Decision Making - aka switch between states */
  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {

    Entity guy_id = (Entity)*e;
    /** DEBUG */
    GuyBrain *brain = ecs->get_component_for_entity<GuyBrain>(guy_id);
    Position *pos = ecs->get_component_for_entity<Position>(guy_id);
    if (brain->die_timer - dt <= 0 && brain->die_timer > 0) {
      Collision w = {CollisionType::NO_OP, {}};
      Collider c = {CollisionShapeType::CIRCLE, {pos->x, pos->y, 6}, w};
      ecs->add_component_to_entity<Collider>(guy_id, c);
      grid->update_entity(guy_id, *pos, c);

      Visible *vis = ecs->get_component_for_entity<Visible>(guy_id);
      vis->frame = GuyAnim.NORM;
      vis->anim_timer = 0;
      vis->texture = gbs_ts.get("guy_sheet");
    }
    brain->die_timer -= dt;
  }

  g_handle_collisions(dt, ecs, grid);
  // gs_wander(dt, ecs);
}

void GuyBrainSystem::g_handle_collisions(float dt, ECS *ecs,
                                         CollisionGrid *grid) {
  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {

    Entity guy_id = (Entity)*e;

    if (!ecs->entity_has_component<Collided>(guy_id))
      continue;

    if (guy_brain_debug) {
      std::cout << "Guy (" << guy_id << ") has collisions" << std::endl;
    }

    Collided *co = ecs->get_component_for_entity<Collided>(guy_id);

    for (int c = 0; c < co->num_collisions; c++) {
      Collision col = co->collisions[c];
      // Switch through collisions
      switch (col.type) {
      case CollisionType::SQUISH: {
        GuySM::die(guy_id, ecs, grid);
        break;
      }

      case CollisionType::GO_SOMEWHERE_ELSE: {
        if (co->num_collisions > 1)
          break;
        g_Wandering *w = GuySM::enter_wandering(guy_id, ecs);
        Position *p = ecs->get_component_for_entity<Position>(guy_id);

        Vec2 pos_away_from = Vec2(col.data.go_somewhere_else.pos_away_from_x,
                                  col.data.go_somewhere_else.pos_away_from_y);

        Vec2 away_from = Vec2(p->x, p->y) - pos_away_from;
        float angle_away = away_from.get_angle_facing();
        int new_angle = Random::rand_range(angle_away - 60, angle_away + 60);

        Vec2 dir = Vec2(1, 0);
        dir.face_angle(new_angle);
        w->dir = dir;
      }
      default: {
        break;
      }
      }
    }
  }
}

/** The guy wanders around aimlessly until they get in range of something cooler
 * Thusly, they should probably be looking around as well...
 */
void gs_wander(float dt, ECS *ecs) {
  /** Wandering */
  std::shared_ptr<ComponentArray<g_Wandering>> comp_wandering =
      ecs->get_component_array<g_Wandering>();

  for (int i = 0; i < comp_wandering->get_num_components(); i++) {
    Entity e = comp_wandering->get_entity_from_idx(i);

    g_Wandering *wander_data = comp_wandering->get_editable_data(e);
    Transform *t = ecs->get_component_for_entity<Transform>(e);
    Position *p = ecs->get_component_for_entity<Position>(e);

    wander_data->timer -= dt;
    t->vel_x = wander_data->dir.x * wander_data->speed;
    t->vel_y = wander_data->dir.y * wander_data->speed;

    if (wander_data->timer < 0) {
      int angle = Random::rand_range(0, 360);
      int speed = Random::rand_range(20, 50);
      Vec2 dir = Vec2(1, 0);
      dir.face_angle(angle);
      float timer = Random::rand_range(2, 6) / 2.f;

      wander_data->dir = dir;
      wander_data->speed = speed;
      wander_data->timer = timer;
    }

    // Make guy decide to turn around if they're about to walk off the edge
    int angle_min = 0;
    int angle_max = 0;
    if (p->y < 5 && wander_data->dir.y < 0) {
      angle_min = 90;
      angle_max = 270;
    } else if (p->y > WINDOW_HEIGHT - 5 && wander_data->dir.y > 0) {
      angle_min = -90;
      angle_max = 90;
    }
    if (p->x < 5 && wander_data->dir.x < 0) {
      angle_min = 0;
      angle_max = 180;
    } else if (p->x > WINDOW_WIDTH - 5 && wander_data->dir.x > 0) {
      angle_min = 180;
      angle_max = 360;
    }
    if (angle_min + angle_max != 0) {
      int angle = Random::rand_range(angle_min, angle_max);
      Vec2 dir = Vec2(0, -1);
      dir.face_angle(angle);
      wander_data->dir = dir;
    }
  }
}
