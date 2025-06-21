#include "components/Components.hpp"
#include <anim/GuyAnim.hpp>
#include <data/TextureStore.hpp>
#include <state_machines/GuySM.h>

#include <components/GuyComponents.hpp>

TextureStore &guy_sm_texture_store = TextureStore::getInstance();

void GuySM::enter_wandering(Entity guy_id, ECS *main_ecs) {

  int angle = rand() % 360;
  int speed = 20 + rand() % 30; // 20 - 50
  Vec2 dir = Vec2(1, 0);
  dir.face_angle(angle);
  float timer = (2 + rand() % 10) / 2.f;

  g_Wandering w = {timer, speed, dir};

  main_ecs->add_component_to_entity<g_Wandering>(guy_id, w);

  GuyBrain *g_Brain = main_ecs->get_component_for_entity<GuyBrain>(guy_id);
  g_Brain->cur_state = GuyState::WANDERING;
}

void GuySM::die(Entity guy_id, ECS *ecs) {
  Visible *vis = ecs->get_component_for_entity<Visible>(guy_id);

  vis->frame = GuyAnim.SQUISH0;
  vis->anim_timer = 0;
  vis->texture = guy_sm_texture_store.get("squish_sheet");

  ecs->remove_component_from_entity<ScanningFor>(guy_id);
  ecs->remove_component_from_entity<Transform>(guy_id);
  ecs->remove_component_from_entity<g_Wandering>(guy_id);
  ecs->remove_component_from_entity<GuyBrain>(guy_id);
  ecs->remove_component_from_entity<Collider>(guy_id);
  ecs->remove_component_from_entity<Collided>(guy_id);
}
