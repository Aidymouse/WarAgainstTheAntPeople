#pragma once

#include "systems/PhysicsSystem.h"
#include "systems/DrawSystem.h"
#include <engine/GameState.h>
#include <memory>

class MainState : public GameState {
	std::shared_ptr<PhysicsSystem> sys_physics;
	std::shared_ptr<DrawSystem> sys_draw;
public:
	MainState();
	void update(float dt) override;
	void draw(sf::RenderTarget* target) override;
	void leave_state() override {};
	void enter_state() override {};
};
