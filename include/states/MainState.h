#pragma once

#include "engine/CollisionGrid.h"
#include "systems/CollisionHandlerSystem.h"
#include "systems/DrawSystem.h"
#include "systems/PersuingSystem.h"
#include "systems/ScanningSystem.h"
#include "systems/ToolMouse.h"
#include "systems/TransformSystem.h"
#include <ecs/ECS.hpp>
#include <engine/GameState.h>
#include <memory>

class MainState : public GameState {
  std::shared_ptr<ToolMouse> sys_toolmouse;
  std::shared_ptr<DrawSystem> sys_draw;
  std::shared_ptr<ScanningSystem> sys_scanning;
  std::shared_ptr<PersuingSystem> sys_persuing;
  std::shared_ptr<CollisionHandlerSystem> sys_collision_handler;
  std::shared_ptr<TransformSystem> sys_transform;

  float timer_max_scrap_spawns = 5;
  float timer_scrap_spawns = 5;

  ECS main_ecs;
  CollisionGrid main_grid;

public:
  MainState();
  void update(float dt) override;
  void draw(sf::RenderTarget *target) override;

  void handle_click(const sf::Event::MouseButtonPressed *evt) override;
  void handle_mousemove(const sf::Event::MouseMoved *evt) override;

  void leave_state() override {};
  void enter_state() override {};
};
