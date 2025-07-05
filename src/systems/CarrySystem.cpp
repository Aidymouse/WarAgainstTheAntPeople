
#include "engine/CollisionGrid.h"
#include <components/Components.hpp>
#include <components/GuyComponents.hpp>
#include <components/HivemindComponents.hpp>
#include <systems/CarrySystem.h>

void process_pickup(float dt, std::set<Entity> *registered_entities, ECS *ecs,
                    CollisionGrid *grid);
void strip_invalid_carrieds(ECS *ecs);

void CarrySystem::update(float dt, ECS *ecs, CollisionGrid *grid) {
  strip_invalid_carrieds(ecs);
  process_pickup(dt, &registered_entities, ecs, grid);
}

/** It's possible that the thing a guy is carrying has been destroyed 
 * We only have a carrier-> carried relationship so we check here to strip them out */
void strip_invalid_carrieds(ECS *ecs) {
  std::shared_ptr<ComponentArray<Carrier>> comp_carriers =
      ecs->get_component_array<Carrier>();
  for (int c = 0; c < comp_carriers->get_num_components(); c++) {
    // Entity c_ent = comp_carriers->get_entity_from_idx(c);
    Carrier *ca = comp_carriers->get_editable_data_from_idx(c);

    if (!ca->carried_entity.has_value())
      return;

    Entity carried_ent = ca->carried_entity.value();
    if (!ecs->entity_has_component<Carryable>(carried_ent)) {
      ca->carried_entity.reset();
    }
  }
}

void process_pickup(float dt, std::set<Entity> *registered_entities, ECS *ecs,
                    CollisionGrid *grid) {
  std::shared_ptr<ComponentArray<Carrier>> comp_carrier = ecs->get_component_array<Carrier>();

  std::shared_ptr<ComponentArray<Carryable>> comp_carryable = ecs->get_component_array<Carryable>();

  for (auto carryable_e = registered_entities->begin();
       carryable_e != registered_entities->end(); carryable_e++) {
    Entity carryable_ent = (Entity)*carryable_e;

    Collider *carryable_col = ecs->get_component_for_entity<Collider>(carryable_ent);

    std::set<Entity> collided = grid->get_collisions(*carryable_col, ecs);
    for (auto collided_e = collided.begin(); collided_e != collided.end();
         collided_e++) {
      Entity collided_ent = (Entity)*collided_e;

      if (collided_ent == carryable_ent) continue;

      Signature s;
      s[COMP_SIG::HANDSFREE] = 1;
      s[COMP_SIG::GUY_BRAIN] = 1;
      // s[COMP_SIG::CARRIER] = 1;

      if (ecs->entity_has_components(collided_ent, s)) {

        Entity pickup_id = carryable_ent;
        Entity guy_id = collided_ent;

        // Set up the hivemind and carryable state
        if (!ecs->entity_has_component<hv_Brain>(pickup_id)) {
          hv_Brain newB;
          for (int i = 0; i < MAX_ENTITIES_IN_HIVEMIND; i++) {
            newB.entities[i] = -1;
          }
          newB.num_entities = 0;

          ecs->add_component_to_entity<hv_Brain>(pickup_id, newB);
          // b.num_entities = 1;
          // b.entities[0] = guy_id;

          ecs->add_component_to_entity<ScanningFor>(
              pickup_id, {{
			SCAN_VALUES::SV_BUILDSITE_WANT_SCRAP,
			SCAN_VALUES::SV_CARRIED_SCRAP,
                        SCAN_VALUES::SV_SCRAP_METAL,
                        SCAN_VALUES::SV_CARRIED_SCRAP_FULL,
			},
                          {500, 500, 500, 500}});
          ecs->add_component_to_entity<Transform>(pickup_id, {0, 0, 0});
          // ecs->add_component_to_entity<GuyBrain>(pickup_id,
          //                                        {GuyState::SEEKING, 0});
          // GuySM::enter_wandering(pickup_id, ecs);

          if (ecs->entity_has_component<Scannable>(pickup_id)) {
            Scannable *s = ecs->get_component_for_entity<Scannable>(pickup_id);
            s->scan_value = SCAN_VALUES::SV_CARRIED_SCRAP;
            //std::cout << "Set new scan value" << s->scan_value << std::endl;
          }

          // ecs->debug_cout_entity_state(pickup_id);
        }

        // Update hivemind and carrier status
        hv_Brain *b = ecs->get_component_for_entity<hv_Brain>(pickup_id);
        Carryable *c = ecs->get_component_for_entity<Carryable>(pickup_id);

        bool already_in = false;
        for (int in = 0; in < b->num_entities; in++) {
          if (b->entities[in] == guy_id) {
            already_in = true;
            break;
          }
        }

        if (!already_in && c->carriers_count < c->carrier_limit) {
          // Start carrying
          ecs->remove_component_from_entity<ScanningFor>(guy_id);
          ecs->remove_component_from_entity<Persuing>(guy_id);
          ecs->remove_component_from_entity<HandsFree>(guy_id);

          int n = b->num_entities;
          b->entities[b->num_entities] = guy_id;
          b->num_entities += 1;

          Position *guy_pos = ecs->get_component_for_entity<Position>(guy_id);

          Position *pickup_pos = ecs->get_component_for_entity<Position>(pickup_id);

          hv_Participant guy_hv;
          Vec2 off = Vec2(guy_pos->x, guy_pos->y) - Vec2(pickup_pos->x, pickup_pos->y);
          guy_hv.offset = off;

          ecs->add_component_to_entity(guy_id, guy_hv);

          // ecs->remove_component_from_entity<Collider>(guy_id);
          // ecs->remove_component_from_entity<Collided>(guy_id);

          c->carriers_count += 1;
          // std::cout << "Adding [" << guy_id << "] to carryable " <<
          // pickup_id
          //           << "(" << c->carriers_count << " / " <<
          // c->carrier_limit
          //           << ")" << std::endl;

          // ecs->remove_component_from_entity<Transform>(guy_id);
          Transform *trans = ecs->get_component_for_entity<Transform>(guy_id);
          trans->vel_x = 0;
          trans->vel_y = 0;
          trans->vel_z = 0;

          if (c->carriers_count == c->carrier_limit) {
            Scannable *picked_up_scannable = ecs->get_component_for_entity<Scannable>(pickup_id);
            picked_up_scannable->scan_value = SCAN_VALUES::SV_CARRIED_SCRAP_FULL;
          }
        }
      }
    }
  }
}
