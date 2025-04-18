#include "SDL3/SDL_events.h"
#include "anim/ToolAnim.hpp"
#include "ecs/Entity.hpp"
#include "engine/Collisions.h"
#include "systems/TransformSystem.h"
#include <string>
#include <util/DrawFns.h>

#include <engine/CollisionGrid.h>
#include <states/MainState.h>
#include <util/Helper.h>

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

  Visible v = {texture_store.get("guy_sheet"), GuyAnim.NORM, 0, {-7, -11}};
  float x = (float)(rand() % 800);
  float y = (float)(rand() % 600);
  Position p = {x, y, 0};
  Collider c = {CollisionShapeType::CIRCLE, {x, y, 6}, 0};
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

  COMP_SIG scanning_sigs[3] = {COMP_SIG::SCANNING_FOR, COMP_SIG::POSITION, COMP_SIG::TRANSFORM};
  sys_scanning = main_ecs.register_system<ScanningSystem>(scanning_sigs, 3);

  COMP_SIG follows_mouse[2] = {COMP_SIG::FOLLOWS_MOUSE, COMP_SIG::POSITION};
  sys_follows_mouse = main_ecs.register_system<FollowsMouseSystem>(follows_mouse, 2);
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
      hand,
      {texture_store.get("tool_hand"), ToolAnim.HAND_NORM, 0, {-16, -16}});
  main_ecs.add_component_to_entity<FollowsMouse>(hand, {});

  //   Mallet

  // Guys
  for (int g = 0; g < 10000; g++) {
    add_guy(&main_ecs, &main_grid);
  }
  //
  for (int s = 0; s < 3; s++) {
    add_scrap(&main_ecs);
  }
}

MainState::~MainState() {}

void MainState::handle_mousemove() {}

void MainState::handle_click(
    SDL_Event
        *event) { // We can be sure it's an SDL_MouseButtonEvent, i checked.
  int btn = event->button.button;
  std::cout << btn << std::endl;

  Collider mouse = {
      CollisionShapeType::CIRCLE, {event->button.x, event->button.y, 16}, 0};
  // std::set<int> ids = main_grid.get_overlapping_cells(mouse);
  // Helper::cout_cell_ids(&ids);

  std::set<Entity> collided_ids = main_grid.get_collisions(mouse, &main_ecs);
  Helper::cout_set(&collided_ids);

  for (auto e = collided_ids.begin(); e != collided_ids.end(); e++) {
    Entity ent = (Entity)*e;

    Visible *vis = main_ecs.get_component_for_entity<Visible>(ent);

    vis->frame = GuyAnim.SQUISH0;
    vis->anim_timer = 0;
    vis->texture = texture_store.get("squish_sheet");

    // main_ecs.remove_component_from_entity<Transform>(ent);
    main_ecs.remove_component_from_entity<ScanningFor>(ent);
    main_ecs.remove_component_from_entity<Transform>(ent);
  }
}

// void MainState::handle_mousemove() {}

void MainState::update(float dt) {
  sys_transform->update(dt, &main_grid, &main_ecs);
  sys_scanning->update(dt, &main_ecs);
  sys_follows_mouse->update(dt, &main_ecs, &main_grid);

  sys_draw->update(dt, &main_ecs);

  // std::cout << "Grid After Update" << std::endl;
  // main_grid.debug_display();
}

void MainState::draw(SDL_Renderer *renderer) {
  sys_draw->draw(renderer, &main_ecs);

  float mX, mY;
  SDL_GetMouseState(&mX, &mY);
  // DrawFns::RenderCircle(renderer, mX, mY, 16);
  // main_grid.debug_draw_grid(renderer);
}
