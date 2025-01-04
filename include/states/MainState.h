#pragma once

#include "systems/DrawSystem.h"
#include "systems/ToolClick.h"
#include <engine/GameState.h>
#include <memory>

class MainState : public GameState {
	std::shared_ptr<ToolClick> sys_toolclick;
	std::shared_ptr<DrawSystem> sys_draw;
public:
	MainState();
	void update(float dt) override;
	void draw(sf::RenderTarget* target) override;

	void handle_click(const sf::Event::MouseButtonPressed* evt) override;

	void leave_state() override {};
	void enter_state() override {};
};
