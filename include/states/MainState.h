#pragma once

#include "SDL3/SDL_events.h"
#include "ecs/Entity.hpp"
#include "systems/FollowsMouseSystem.h"
#include "systems/GuyBrainSystem.h"
#include "systems/HivemindBrainSystem.h"
#include "systems/ScanningSystem.h"
#include "systems/TransformSystem.h"
#include <SDL3/SDL.h>
#include <ecs/ECS.hpp>
#include <engine/CollisionGrid.h>
#include <engine/GameState.h>
#include <memory>
#include <systems/CollisionSystem.h>
#include <systems/DrawSystem.h>
#include <systems/SortedDrawSystem.h>

class MainState : public GameState {

  std::shared_ptr<DrawSystem> sys_draw;
  std::shared_ptr<SortedDrawSystem> sys_sorted_draw;
  std::shared_ptr<TransformSystem> sys_transform;
  std::shared_ptr<ScanningSystem> sys_scanning;
  std::shared_ptr<FollowsMouseSystem> sys_follows_mouse;
  std::shared_ptr<GuyBrainSystem> sys_guy_brain;
  std::shared_ptr<CollisionSystem> sys_collision;
  std::shared_ptr<HivemindBrainSystem> sys_hivemind_brain;

  Entity main_base = -1;
  Entity tool_hand = -1;

  float timer_max_scrap_spawns = 5;
  float timer_scrap_spawns = 5;

  ECS main_ecs;
  CollisionGrid main_grid;

public:
  MainState();
  ~MainState();

  void load_ecs();

  void update(float dt) override;
  void draw(SDL_Renderer *renderer) override;

  void handle_click(SDL_Event *event) override;
  void handle_keydown(SDL_Event *event) override;
  void handle_mousemove() override;

  void leave_state() override {};
  void enter_state() override {};
};
