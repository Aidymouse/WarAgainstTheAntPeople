#include "SDL3/SDL_events.h"
#include "anim/ToolAnim.hpp"
#include "components/Collisions.hpp"
#include "ecs/Entity.hpp"
#include "engine/Collisions.h"
#include "systems/BuildSystem.h"
#include "systems/GuyBrainSystem.h"
#include "systems/HivemindBrainSystem.h"
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
#include <components/HivemindComponents.hpp>
#include <data/TextureStore.hpp>
#include <systems/DrawSystem.h>
#include <systems/FollowsMouseSystem.h>
#include <systems/ScanningSystem.h>
#include <systems/ShootSystem.h>
#include <systems/DamageSystem.h>

#include <anim/GuyAnim.hpp>
#include <anim/NotMovingAnim.hpp>

#include <util/Spawners.h>

#include <ProjectConfig.h>

const bool mainstate_debug = false;

TextureStore &texture_store = TextureStore::getInstance();

MainState::MainState() {

	TextureStore &texture_store = TextureStore::getInstance();

	load_ecs();

	// Main Base
	main_base = main_ecs.add_entity();
	float base_x = WINDOW_WIDTH / 2.f;
	float base_y = WINDOW_HEIGHT / 2.f;
	main_ecs.add_component_to_entity<Position>(main_base, {base_x, base_y});
	CollisionShape base_circle;
	base_circle.circle = {base_x, base_y, 50};
	Collision base_collision = {CollisionType::GO_SOMEWHERE_ELSE, {(int)base_x, (int)base_y}};
	Collider base_c = {CollisionShapeType::CIRCLE, base_circle, base_collision};
	main_ecs.add_component_to_entity<Collider>(main_base, base_c);
	main_ecs.add_component_to_entity<Damageable>(main_base, {
		100,
		1
	});

	// Hand
	tool_hand = main_ecs.add_entity();
	main_ecs.add_component_to_entity<Position>(tool_hand, {0, 0, 5});
	main_ecs.add_component_to_entity<SortedVisible>( tool_hand, {texture_store.get("tool_hand"), ToolAnim.HAND_NORM, 0, {-16, -16}});
	main_ecs.add_component_to_entity<FollowsMouse>(tool_hand, {-1});

	// Guys
	// The benchmark is 3000
	// If we want to hit 10,000 then I'll need to bust out Vulkan I think
	for (int g = 0; g < 3000; g++) {
		Spawners::add_guy(&main_ecs, &main_grid);
	}
	for (int s = 0; s < 60; s++) {
		Spawners::add_scrap(&main_ecs);
	}

	// if (mainstate_debug) std::cout << "Removing entity" << std::endl;
	// main_ecs.remove_entity(3);
}

MainState::~MainState() {}

void MainState::handle_mousemove() {}

void register_collision(Entity ent, ECS *ecs) {}

void MainState::handle_keydown( SDL_Event *event) { // We can be sure it's an ...
	main_ecs.debug_cout_entity_state(2);
}

void MainState::handle_click( SDL_Event *event) { // We can be sure it's an SDL_MouseButtonEvent, i checked.
  int btn = event->button.button;
  if (mainstate_debug) if (mainstate_debug) std::cout << "Clicked: " << btn << std::endl;

  Collision mallet_hit = { CollisionType::SQUISH, {10}, };

  Collider mouse = {CollisionShapeType::CIRCLE, {event->button.x, event->button.y, 16}, mallet_hit}; 
	// std::set<int> ids = main_grid.get_overlapping_cells(mouse);
  // Helper::cout_cell_ids(&ids);

  std::set<Entity> collided_ids = main_grid.get_collisions(mouse, &main_ecs);
  //
  main_ecs.add_component_to_entity<Collider>(tool_hand, mouse);
  // Helper::cout_set(&collided_ids);

  // for (auto e = collided_ids.begin(); e != collided_ids.end(); e++) {
  //   Entity ent = (Entity)*e;
  //
  //   Visible *vis = main_ecs.get_component_for_entity<Visible>(ent);
  //
  //   vis->frame = GuyAnim.SQUISH0;
  //   vis->anim_timer = 0;
  //   vis->texture = texture_store.get("squish_sheet");
  //
  //   Position *pos = main_ecs.get_component_for_entity<Position>(ent);
  //   pos->z = -1;
  //   // main_ecs.remove_component_from_entity<Transform>(ent);
  //   main_ecs.remove_component_from_entity<ScanningFor>(ent);
  //   main_ecs.remove_component_from_entity<Transform>(ent);
  // }
}

// void MainState::handle_mousemove() {}

void MainState::update(float dt) {
  // if (mainstate_debug) std::cout << dt << std::endl;
  if (mainstate_debug) std::cout << "\nNew Frame" << std::endl;


  main_ecs.remove_component_from_entity<Collider>(tool_hand);

  if (mainstate_debug) std::cout << "--- Guy Brain System" << std::endl;
  sys_guy_brain->update(dt, &main_ecs, &main_grid);

  if (mainstate_debug) std::cout << "--- Carry System" << std::endl;
  sys_carry->update(dt, &main_ecs, &main_grid);

  if (mainstate_debug) std::cout << "--- Build System" << std::endl;
  sys_build->update(dt, &main_ecs, &main_grid);

  if (mainstate_debug) std::cout << "--- Transform System" << std::endl;
  sys_transform->update(dt, &main_grid, &main_ecs);

  if (mainstate_debug) std::cout << "--- Scanning System" << std::endl;
  sys_scanning->update(dt, &main_ecs);

  if (mainstate_debug) std::cout << "--- Follows Mouse System" << std::endl;
  sys_follows_mouse->update(dt, &main_ecs, &main_grid);

  if (mainstate_debug) std::cout << "--- Draw System" << std::endl;
  sys_draw->update(dt, &main_ecs);

  if (mainstate_debug) std::cout << "--- Hivemind Brain System" << std::endl;
  sys_hivemind_brain->update(dt, &main_ecs, &main_grid);

  if (mainstate_debug) std::cout << "--- Damage System" << std::endl;
	sys_damage->update(dt, &main_ecs, &main_grid);

	if (mainstate_debug) std::cout << "--- Shoot System" << std::endl;
	sys_shoot->update(dt, &main_ecs, &main_grid);

  // sys_collision->strip_collided(dt, &main_ecs);
  //  Uint32 m = SDL_GetMouseState(nullptr, nullptr);
  //
  //  if (m & SDL_BUTTON_MASK(3)) {
  //    if (mainstate_debug) std::cout << main_ecs.num_entities << std::endl;
  //    add_guy(&main_ecs, &main_grid);
  //  }
  //  if (mainstate_debug) std::cout << "Grid After Update" << std::endl;
  // main_grid.debug_display();
}

void MainState::draw(SDL_Renderer *renderer) {
  sys_draw->draw(renderer, &main_ecs);

  float mX, mY;
  SDL_GetMouseState(&mX, &mY);
  DrawFns::RenderCircle(renderer, WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f, 50);
  // DrawFns::RenderCircle(renderer, mX, mY, 16);
  // main_grid.debug_draw_grid(renderer);
}

void MainState::load_ecs() {
  /** Set up Systems */
  COMP_SIG draw_sigs[3] = {COMP_SIG::POSITION, COMP_SIG::VISIBLE, COMP_SIG::SORTEDVISIBLE}; // It's impossible to register with this system pretty much
  sys_draw = main_ecs.register_system<DrawSystem>(draw_sigs, 3);

  COMP_SIG transform_sigs[2] = {COMP_SIG::TRANSFORM, COMP_SIG::POSITION};
  sys_transform = main_ecs.register_system<TransformSystem>(transform_sigs, 2);

  COMP_SIG scanning_sigs[3] = {COMP_SIG::SCANNING_FOR, COMP_SIG::POSITION, COMP_SIG::TRANSFORM};
  sys_scanning = main_ecs.register_system<ScanningSystem>(scanning_sigs, 3);

  COMP_SIG follows_mouse[2] = {COMP_SIG::FOLLOWS_MOUSE, COMP_SIG::POSITION};
  sys_follows_mouse = main_ecs.register_system<FollowsMouseSystem>(follows_mouse, 2);
  // sys_draw = main_ecs.register_system<DrawSystem>(draw_sig);

  COMP_SIG guy_brain_sig[3] = {COMP_SIG::GUY_BRAIN, COMP_SIG::POSITION, COMP_SIG::VISIBLE};
  sys_guy_brain = main_ecs.register_system<GuyBrainSystem>(guy_brain_sig, 3);

  COMP_SIG hivemind_brain_sig[1] = {COMP_SIG::HV_BRAIN};
  sys_hivemind_brain = main_ecs.register_system<HivemindBrainSystem>(hivemind_brain_sig, 1);

  COMP_SIG carry_sig[2] = {COMP_SIG::CARRYABLE, COMP_SIG::COLLIDER};
  sys_carry = main_ecs.register_system<CarrySystem>(carry_sig, 2);

  COMP_SIG build_sig[1] = {COMP_SIG::BUILDABLE};
  sys_build = main_ecs.register_system<BuildSystem>(build_sig, 1);

  COMP_SIG shoot_sig[1] = {COMP_SIG::SHOOTER};
  sys_shoot = main_ecs.register_system<ShootSystem>(shoot_sig, 1);

	COMP_SIG damage_sig[2] = {COMP_SIG::DAMAGEABLE, COMP_SIG::COLLIDER};
	sys_damage = main_ecs.register_system<DamageSystem>(damage_sig, 1);

  /** Set up components */
  main_ecs.register_component<Position>(COMP_SIG::POSITION);
  main_ecs.register_component<ZEnabled>(COMP_SIG::ZENABLED);

  main_ecs.register_component<Visible>(COMP_SIG::VISIBLE);
  main_ecs.register_component<SortedVisible>(COMP_SIG::SORTEDVISIBLE);
  main_ecs.register_component<Transform>(COMP_SIG::TRANSFORM);

  main_ecs.register_component<FollowsMouse>(COMP_SIG::FOLLOWS_MOUSE);

  // Collisions
  main_ecs.register_component<Collider>(COMP_SIG::COLLIDER);
  main_ecs.register_component<Collided>(COMP_SIG::COLLIDED);

  // Scanning and Persuing
  main_ecs.register_component<ScanningFor>(COMP_SIG::SCANNING_FOR);
  main_ecs.register_component<Scannable>(COMP_SIG::SCANNABLE);
  main_ecs.register_component<Persuing>(COMP_SIG::PERSUING);

  main_ecs.register_component<Carrier>(COMP_SIG::CARRIER);
  main_ecs.register_component<Carryable>(COMP_SIG::CARRYABLE);

  // Building
  main_ecs.register_component<Buildable>(COMP_SIG::BUILDABLE);
  main_ecs.register_component<Resource>(COMP_SIG::RESOURCE);

  // Guy components
  main_ecs.register_component<GuyBrain>(COMP_SIG::GUY_BRAIN);
  main_ecs.register_component<g_Wandering>(COMP_SIG::GUY_WANDERING);

  // Hivemind
  main_ecs.register_component<hv_Brain>(COMP_SIG::HV_BRAIN);
  main_ecs.register_component<hv_Participant>(COMP_SIG::HV_PARTICIPANT);

  main_ecs.register_component<HandsFree>(COMP_SIG::HANDSFREE);

  main_ecs.register_component<Shooter>(COMP_SIG::SHOOTER);
  main_ecs.register_component<Projectile>(COMP_SIG::PROJECTILE);

  main_ecs.register_component<Damageable>(COMP_SIG::DAMAGEABLE);
  main_ecs.register_component<Damager>(COMP_SIG::DAMAGER);
}
