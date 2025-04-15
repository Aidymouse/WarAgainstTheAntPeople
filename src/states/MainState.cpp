#include "anim/ToolAnim.hpp"
#include "engine/Collisions.h"
#include "systems/TransformSystem.h"
#include <string>

#include <engine/CollisionGrid.h>
#include <states/MainState.h>

#include <ecs/ECS.hpp>

#include <SDL3/SDL.h>
#include <data/TextureStore.hpp>
#include <engine/Components.hpp>
#include <systems/DrawSystem.h>
#include <systems/FollowsMouseSystem.h>
#include <systems/ScanningSystem.h>

#include <anim/GuyAnim.hpp>
#include <anim/NotMovingAnim.hpp>

#include <ProjectConfig.h>

TextureStore &texture_store = TextureStore::getInstance();

void add_guy(ECS *ecs, CollisionGrid *grid) {

  Visible v = {texture_store.get("guy_sheet"), GuyAnim.NORM, 0};
  float x = (float)(rand() % 800);
  float y = (float)(rand() % 600);
  Position p = {x, y, 0};
  Collider c = {CollisionShapeType::CIRCLE, {x, y, 4}, 0};
  Entity g = ecs->add_entity();
  ecs->add_component_to_entity<Visible>(g, v);
  ecs->add_component_to_entity<Position>(g, p);
  ecs->add_component_to_entity<Transform>(g, {0, 0, 0});
  ecs->add_component_to_entity<ScanningFor>(g, {SCAN_VALUES::SCRAP});
  ecs->add_component_to_entity<Collider>(g, c);

  grid->update_entity(g, p, c);

  // std::cout << "Added guy [" << g << "] at " << x << ", " << y << std::endl;
}

void add_scrap(ECS *ecs) {
  Visible v = {texture_store.get("scrap_sheet"), NotMovingAnim.SCRAP};
  float x = (float)(rand() % 800);
  float y = (float)(rand() % 600);
  Position p = {x, y, 0};
  Entity s = ecs->add_entity();
  ecs->add_component_to_entity<Visible>(s, v);
  ecs->add_component_to_entity<Position>(s, p);
  ecs->add_component_to_entity<Scannable>(s, {SCAN_VALUES::SCRAP});
}

MainState::MainState() {

  TextureStore &texture_store = TextureStore::getInstance();

  /** Set up Systems */
  COMP_SIG draw_sigs[2] = {COMP_SIG::POSITION, COMP_SIG::VISIBLE};
  sys_draw = main_ecs.register_system<DrawSystem>(draw_sigs, 2);

  COMP_SIG transform_sigs[2] = {COMP_SIG::TRANSFORM, COMP_SIG::POSITION};
  sys_transform = main_ecs.register_system<TransformSystem>(transform_sigs, 2);

  COMP_SIG scanning_sigs[3] = {COMP_SIG::SCANNING_FOR, COMP_SIG::POSITION,
                               COMP_SIG::TRANSFORM};
  sys_scanning = main_ecs.register_system<ScanningSystem>(scanning_sigs, 3);

  COMP_SIG follows_mouse[2] = {COMP_SIG::FOLLOWS_MOUSE, COMP_SIG::POSITION};
  sys_follows_mouse =
      main_ecs.register_system<FollowsMouseSystem>(follows_mouse, 2);
  // sys_draw = main_ecs.register_system<DrawSystem>(draw_sig);

  /** Set up components -- needs to be in order of COMP_SIG */
  main_ecs.register_component<Position>(COMP_SIG::POSITION);
  main_ecs.register_component<Visible>(COMP_SIG::VISIBLE);
  main_ecs.register_component<Transform>(COMP_SIG::TRANSFORM);
  // main_ecs.register_component<Tool>();
  // main_ecs.register_component<Clickable>();

  // main_ecs.register_component<Collider>();
  //
  // main_ecs.register_component<Smashable>();
  //
  main_ecs.register_component<ScanningFor>(COMP_SIG::SCANNING_FOR);
  main_ecs.register_component<Scannable>(COMP_SIG::SCANNABLE);
  main_ecs.register_component<FollowsMouse>(COMP_SIG::FOLLOWS_MOUSE);
  main_ecs.register_component<Collider>(COMP_SIG::COLLIDER);
  // // main_ecs.register_component<Persuing>();
  //
  // main_ecs.register_component<Carrier>();
  // main_ecs.register_component<Carryable>();
  //
  // main_ecs.register_component<Tool>();

  /** Initial Entities */

  //   Hand
  Entity hand = main_ecs.add_entity();
  main_ecs.add_component_to_entity<Position>(hand, {0, 0});
  main_ecs.add_component_to_entity<Visible>(
      hand, {texture_store.get("tool_hand"), ToolAnim.HAND_NORM});
  main_ecs.add_component_to_entity<FollowsMouse>(hand, {});
  //   Mallet

  // Guys
  for (int g = 0; g < 100; g++) {
    add_guy(&main_ecs, &main_grid);
  }

  for (int s = 0; s < 3; s++) {
    add_scrap(&main_ecs);
  }
}

MainState::~MainState() {}

void MainState::handle_click() {}

void MainState::handle_mousemove() {}

void MainState::update(float dt) {
  sys_transform->update(dt, &main_grid, &main_ecs);
  sys_scanning->update(dt, &main_ecs);
  sys_follows_mouse->update(dt, &main_ecs, &main_grid);

  sys_draw->update(dt, &main_ecs);

  std::cout << "Grid After Update" << std::endl;
  main_grid.debug_display();
}

void MainState::draw(SDL_Renderer *renderer) {
  sys_draw->draw(renderer, &main_ecs);

  main_grid.debug_draw_grid(renderer);
}
