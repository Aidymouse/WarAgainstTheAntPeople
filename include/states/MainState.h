#pragma once

#include "systems/DrawSystem.h"
#include "systems/ToolMouse.h"
#include <engine/GameState.h>
#include <memory>

class MainState : public GameState {
	std::shared_ptr<ToolMouse> sys_toolmouse;
	std::shared_ptr<DrawSystem> sys_draw;
public:
	MainState();
	void update(float dt) override;
	void draw(sf::RenderTarget* target) override;

	void handle_click(const sf::Event::MouseButtonPressed* evt) override;
	void handle_mousemove(const sf::Event::MouseMoved* evt) override;

	void leave_state() override {};
	void enter_state() override {};
};
