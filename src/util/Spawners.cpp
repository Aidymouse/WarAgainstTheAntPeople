#include <data/TextureStore.hpp>

#include <state_machines/GuySM.h>
#include <util/Spawners.h>

#include <components/GuyComponents.hpp>
#include <ecs/ECS.hpp>
#include <engine/CollisionGrid.h>

#include "anim/GuyAnim.hpp"
#include "anim/NotMovingAnim.hpp"
#include "components/Collisions.hpp"
#include "util/Random.h"

TextureStore &spawners_texture_store = TextureStore::getInstance();

void Spawners::add_guy(ECS *ecs, CollisionGrid *grid) {

  Visible v = {
      spawners_texture_store.get("guy_sheet"), GuyAnim.NORM, 0, {-7, -11}};
  float x = (float)(Random::rand_range(0, WINDOW_WIDTH));
  float y = (float)(Random::rand_range(0, WINDOW_HEIGHT));
  Position p = {x, y, 0};
  // Position p = {WINDOW_WIDTH / 2, 400, 0};
  Collision w = {CollisionType::NO_OP, {}};
  Collider c = {CollisionShapeType::CIRCLE, {x, y, 6}, w};
  Entity g = ecs->add_entity();
  ecs->add_component_to_entity<Visible>(g, v);
  ecs->add_component_to_entity<Position>(g, p);
  ecs->add_component_to_entity<Transform>(g, {0, 0, 0});
  ecs->add_component_to_entity<Collider>(g, c);
  ecs->add_component_to_entity<GuyBrain>(g, {});

  if (rand() % 100 < 10) {
    ecs->add_component_to_entity<ScanningFor>(g, {SCAN_VALUES::SV_SCRAP_METAL});
  } else {
    g_Wandering *w = GuySM::enter_wandering(g, ecs);
  }

  grid->update_entity(g, p, c);

  // std::cout << "Added guy [" << g << "] at " << x << ", " << y << std::endl;
}

void Spawners::add_scrap(ECS *ecs) {
  Visible v = {spawners_texture_store.get("scrap_sheet"), NotMovingAnim.SCRAP};
  float x = (float)(Random::rand_range(0, WINDOW_WIDTH));
  float y = (float)(Random::rand_range(0, WINDOW_HEIGHT));
  Position p = {x, y};
  Carryable carry_data = {0, 0, 10}; // TODO should come from somewhere dynamic
  Entity s = ecs->add_entity();
  ecs->add_component_to_entity<Visible>(s, v);
  ecs->add_component_to_entity<Position>(s, p);
  ecs->add_component_to_entity<Scannable>(s, {SCAN_VALUES::SV_SCRAP_METAL});
  ecs->add_component_to_entity<Carryable>(s, carry_data);
}
