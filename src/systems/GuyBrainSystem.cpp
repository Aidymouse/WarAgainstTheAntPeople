// System that handles making decisions for a guy. The only thing we know for
// sure is that we have a guy present. This is, like, probably against ECS ethos
// or some shit.
//
#include "components/Collisions.hpp"
#include "components/Components.hpp"
#include "components/HivemindComponents.hpp"
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

    if (ecs->entity_has_component<hv_Participant>(guy_id) ||
        ecs->entity_has_component<hv_Brain>(guy_id)) {
      continue;
    }

    if (!ecs->entity_has_component<Persuing>(guy_id) &&
        !ecs->entity_has_component<g_Wandering>(guy_id)) {
      GuySM::enter_wandering(guy_id, ecs);
    }

    /** DEBUG */
  }

  // Sub system calls
  // g_handle_collisions(dt, ecs, grid);
  gs_wander(dt, ecs);
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
      bool cancel_remaining_collision_checks = false;
      Collision col = co->collisions[c];
      // Switch through collisions
      switch (col.type) {

      case CollisionType::IDENTIFIER: {
        if (col.data.identifier.id == Identifier::SCRAP_METAL) {
          // Transform into PICK_ME_UP
          co->collisions[c].type = CollisionType::PICK_ME_UP;
          co->collisions[c].data.pick_me_up = {
              co->collisions[c].data.identifier.entity_id};
        }

        c--;

        break;
      }

      case CollisionType::SQUISH: {
        GuySM::die(guy_id, ecs, grid);
        // return; // Don't handle any more collisions after a guy has died!
        cancel_remaining_collision_checks = true;
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
        break;
      }
      // case CollisionType::PICK_ME_UP: {
      //   Entity pickup_id = col.data.pick_me_up.to_pick_up;
      //
      //   // Set up the hivemind and carryable state
      //   if (!ecs->entity_has_component<hv_Brain>(pickup_id)) {
      //     hv_Brain newB;
      //     for (int i = 0; i < MAX_ENTITIES_IN_HIVEMIND; i++) {
      //       newB.entities[i] = -1;
      //     }
      //     newB.num_entities = 0;
      //
      //     ecs->add_component_to_entity<hv_Brain>(pickup_id, newB);
      //     // b.num_entities = 1;
      //     // b.entities[0] = guy_id;
      //
      //     ecs->add_component_to_entity<ScanningFor>(
      //         pickup_id, {{SCAN_VALUES::SV_CARRIED_SCRAP,
      //                      SCAN_VALUES::SV_CARRIED_SCRAP_FULL,
      //                      SCAN_VALUES::SV_SCRAP_METAL, 0},
      //                     {500, 500, 500, 0}});
      //     ecs->add_component_to_entity<Transform>(pickup_id, {0, 0, 0});
      //     // ecs->add_component_to_entity<GuyBrain>(pickup_id,
      //     //                                        {GuyState::SEEKING, 0});
      //     // GuySM::enter_wandering(pickup_id, ecs);
      //
      //     if (ecs->entity_has_component<Scannable>(pickup_id)) {
      //       Scannable *s =
      //       ecs->get_component_for_entity<Scannable>(pickup_id);
      //       s->scan_value = SCAN_VALUES::SV_CARRIED_SCRAP;
      //       std::cout << "Set new scan value" << s->scan_value << std::endl;
      //     }
      //
      //     // ecs->debug_cout_entity_state(pickup_id);
      //   }
      //
      //   // Update hivemind and carrier status
      //   hv_Brain *b = ecs->get_component_for_entity<hv_Brain>(pickup_id);
      //   Carryable *c = ecs->get_component_for_entity<Carryable>(pickup_id);
      //
      //   bool already_in = false;
      //   for (int in = 0; in < b->num_entities; in++) {
      //     if (b->entities[in] == guy_id) {
      //       already_in = true;
      //       break;
      //     }
      //   }
      //
      //   if (!already_in && c->carriers_count < c->carrier_limit) {
      //     // Start carrying
      //     ecs->remove_component_from_entity<ScanningFor>(guy_id);
      //     ecs->remove_component_from_entity<Persuing>(guy_id);
      //
      //     int n = b->num_entities;
      //     b->entities[b->num_entities] = guy_id;
      //     b->num_entities += 1;
      //
      //     Position *guy_pos =
      //     ecs->get_component_for_entity<Position>(guy_id);
      //
      //     Position *pickup_pos =
      //         ecs->get_component_for_entity<Position>(pickup_id);
      //
      //     hv_Participant guy_hv;
      //     Vec2 off =
      //         Vec2(pickup_pos->x, pickup_pos->y) - Vec2(guy_pos->x,
      //         guy_pos->y);
      //     guy_hv.offset = off;
      //
      //     ecs->add_component_to_entity(guy_id, guy_hv);
      //
      //     // ecs->remove_component_from_entity<Collider>(guy_id);
      //     // ecs->remove_component_from_entity<Collided>(guy_id);
      //
      //     c->carriers_count += 1;
      //     // std::cout << "Adding [" << guy_id << "] to carryable " <<
      //     pickup_id
      //     //           << "(" << c->carriers_count << " / " <<
      //     c->carrier_limit
      //     //           << ")" << std::endl;
      //
      //     // ecs->remove_component_from_entity<Transform>(guy_id);
      //     Transform *trans =
      //     ecs->get_component_for_entity<Transform>(guy_id); trans->vel_x = 0;
      //     trans->vel_y = 0;
      //     trans->vel_z = 0;
      //
      //     if (c->carriers_count == c->carrier_limit) {
      //       Scannable *picked_up_scannable =
      //           ecs->get_component_for_entity<Scannable>(pickup_id);
      //       picked_up_scannable->scan_value =
      //           SCAN_VALUES::SV_CARRIED_SCRAP_FULL;
      //     }
      //   }
      //
      //   break;
      // }
      default: {
        break;
      }
      }

      if (cancel_remaining_collision_checks)
        break;
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
