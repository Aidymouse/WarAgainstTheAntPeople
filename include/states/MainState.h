#pragma once

#include "systems/FollowsMouseSystem.h"
#include "systems/ScanningSystem.h"
#include "systems/TransformSystem.h"
#include <SDL3/SDL.h>
#include <ecs/ECS.hpp>
#include <engine/CollisionGrid.h>
#include <engine/GameState.h>
#include <memory>
#include <systems/DrawSystem.h>

class MainState : public GameState {

  std::shared_ptr<DrawSystem> sys_draw;
  std::shared_ptr<TransformSystem> sys_transform;
  std::shared_ptr<ScanningSystem> sys_scanning;
  std::shared_ptr<FollowsMouseSystem> sys_follows_mouse;

  float timer_max_scrap_spawns = 5;
  float timer_scrap_spawns = 5;

  ECS main_ecs;
  CollisionGrid main_grid;

public:
  MainState();
  ~MainState();
  void update(float dt) override;
  void draw(SDL_Renderer *renderer) override;

  void handle_click() override;
  void handle_mousemove() override;

  void leave_state() override {};
  void enter_state() override {};
};
