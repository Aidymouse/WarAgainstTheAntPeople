#include "SDL3/SDL_events.h"
#include "anim/ToolAnim.hpp"
#include "ecs/Entity.hpp"
#include "engine/Collisions.h"
#include "systems/GuyBrainSystem.h"
#include "systems/TransformSystem.h"
#include <string>
#include <util/DrawFns.h>

#include <engine/CollisionGrid.h>
#include <states/MainState.h>
#include <util/Helper.h>

#include <ecs/ECS.hpp>

#include <SDL3/SDL.h>
#include <components/Components.hpp>
#include <components/GuyComponents.hpp>
#include <data/TextureStore.hpp>
#include <systems/DrawSystem.h>
#include <systems/FollowsMouseSystem.h>
#include <systems/ScanningSystem.h>
#include <systems/SortedDrawSystem.h>

#include <anim/GuyAnim.hpp>
#include <anim/NotMovingAnim.hpp>

#include <util/Spawners.h>

#include <ProjectConfig.h>

const bool mainstate_debug = false;

TextureStore &texture_store = TextureStore::getInstance();

MainState::MainState() {

  TextureStore &texture_store = TextureStore::getInstance();

  load_ecs();

  //   Hand
  Entity hand = main_ecs.add_entity();
  main_ecs.add_component_to_entity<Position>(hand, {0, 0, 5});
  main_ecs.add_component_to_entity<SortedVisible>(
      hand,
      {texture_store.get("tool_hand"), ToolAnim.HAND_NORM, 0, {-16, -16}});
  main_ecs.add_component_to_entity<FollowsMouse>(hand, {});

  // Guys
  // The benchmark is 3000
  // If we want to hit 10,000 then I'll need to bust out Vulkan I think
  for (int g = 0; g < 3000; g++) {
    Spawners::add_guy(&main_ecs, &main_grid);
  }
  for (int s = 0; s < 6; s++) {
    Spawners::add_scrap(&main_ecs);
  }
}

MainState::~MainState() {}

void MainState::handle_mousemove() {}

void MainState::handle_click(
    SDL_Event
        *event) { // We can be sure it's an SDL_MouseButtonEvent, i checked.
  int btn = event->button.button;
  if (mainstate_debug)
    std::cout << "Clicked: " << btn << std::endl;

  Collider mouse = {
      CollisionShapeType::CIRCLE, {event->button.x, event->button.y, 16}, 0};
  // std::set<int> ids = main_grid.get_overlapping_cells(mouse);
  // Helper::cout_cell_ids(&ids);

  std::set<Entity> collided_ids = main_grid.get_collisions(mouse, &main_ecs);
  // Helper::cout_set(&collided_ids);

  for (auto e = collided_ids.begin(); e != collided_ids.end(); e++) {
    Entity ent = (Entity)*e;

    Visible *vis = main_ecs.get_component_for_entity<Visible>(ent);

    vis->frame = GuyAnim.SQUISH0;
    vis->anim_timer = 0;
    vis->texture = texture_store.get("squish_sheet");

    Position *pos = main_ecs.get_component_for_entity<Position>(ent);
    pos->z = -1;
    // main_ecs.remove_component_from_entity<Transform>(ent);
    main_ecs.remove_component_from_entity<ScanningFor>(ent);
    main_ecs.remove_component_from_entity<Transform>(ent);
  }
}

// void MainState::handle_mousemove() {}

void MainState::update(float dt) {
  // std::cout << dt << std::endl;

  sys_guy_brain->update(dt, &main_ecs);

  sys_transform->update(dt, &main_grid, &main_ecs);
  sys_scanning->update(dt, &main_ecs);
  sys_follows_mouse->update(dt, &main_ecs, &main_grid);

  sys_draw->update(dt, &main_ecs);
  sys_sorted_draw->update(dt, &main_ecs);

  // Uint32 m = SDL_GetMouseState(nullptr, nullptr);
  //
  // if (m & SDL_BUTTON_MASK(3)) {
  //   std::cout << main_ecs.num_entities << std::endl;
  //   add_guy(&main_ecs, &main_grid);
  // }
  // std::cout << "Grid After Update" << std::endl;
  // main_grid.debug_display();
}

void MainState::draw(SDL_Renderer *renderer) {
  sys_draw->draw(renderer, &main_ecs);
  sys_sorted_draw->draw(renderer, &main_ecs);

  float mX, mY;
  SDL_GetMouseState(&mX, &mY);
  DrawFns::RenderCircle(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 50);
  // DrawFns::RenderCircle(renderer, mX, mY, 16);
  // main_grid.debug_draw_grid(renderer);
}

void MainState::load_ecs() {
  /** Set up Systems */
  COMP_SIG draw_sigs[2] = {COMP_SIG::POSITION, COMP_SIG::VISIBLE};
  sys_draw = main_ecs.register_system<DrawSystem>(draw_sigs, 2);
  COMP_SIG sorted_draw_sigs[2] = {COMP_SIG::POSITION, COMP_SIG::SORTEDVISIBLE};
  sys_sorted_draw =
      main_ecs.register_system<SortedDrawSystem>(sorted_draw_sigs, 2);

  COMP_SIG transform_sigs[2] = {COMP_SIG::TRANSFORM, COMP_SIG::POSITION};
  sys_transform = main_ecs.register_system<TransformSystem>(transform_sigs, 2);

  COMP_SIG scanning_sigs[3] = {COMP_SIG::SCANNING_FOR, COMP_SIG::POSITION,
                               COMP_SIG::TRANSFORM};
  sys_scanning = main_ecs.register_system<ScanningSystem>(scanning_sigs, 3);

  COMP_SIG follows_mouse[2] = {COMP_SIG::FOLLOWS_MOUSE, COMP_SIG::POSITION};
  sys_follows_mouse =
      main_ecs.register_system<FollowsMouseSystem>(follows_mouse, 2);
  // sys_draw = main_ecs.register_system<DrawSystem>(draw_sig);

  COMP_SIG guy_brain_sig[3] = {COMP_SIG::GUY_BRAIN, COMP_SIG::POSITION,
                               COMP_SIG::VISIBLE};
  sys_guy_brain = main_ecs.register_system<GuyBrainSystem>(guy_brain_sig, 3);

  /** Set up components */
  main_ecs.register_component<Reserved>(COMP_SIG::RESERVED);

  main_ecs.register_component<Position>(COMP_SIG::POSITION);
  main_ecs.register_component<ZEnabled>(COMP_SIG::ZENABLED);

  main_ecs.register_component<Visible>(COMP_SIG::VISIBLE);
  main_ecs.register_component<SortedVisible>(COMP_SIG::SORTEDVISIBLE);
  main_ecs.register_component<Transform>(COMP_SIG::TRANSFORM);

  main_ecs.register_component<ScanningFor>(COMP_SIG::SCANNING_FOR);
  main_ecs.register_component<Scannable>(COMP_SIG::SCANNABLE);
  main_ecs.register_component<FollowsMouse>(COMP_SIG::FOLLOWS_MOUSE);
  main_ecs.register_component<Collider>(COMP_SIG::COLLIDER);

  main_ecs.register_component<GuyBrain>(COMP_SIG::GUY_BRAIN);
  main_ecs.register_component<g_Wandering>(COMP_SIG::GUY_WANDERING);
}
