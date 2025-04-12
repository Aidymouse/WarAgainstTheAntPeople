#pragma once

#include <ecs/ECS.hpp>
#include <engine/GameState.h>
#include <memory>

class MainState : public GameState {

  float timer_max_scrap_spawns = 5;
  float timer_scrap_spawns = 5;

  ECS main_ecs;

public:
  MainState();
  void update(float dt) override;
  void draw() override;

  void handle_click() override;
  void handle_mousemove() override;

  void leave_state() override {};
  void enter_state() override {};
};
