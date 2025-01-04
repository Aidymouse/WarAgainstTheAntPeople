#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <ecs/System.hpp>

class ToolMouse : public System {
	Entity held_tool = -1;
	int mouseX;
	int mouseY;
public:
	void update(float dt);
	void draw(sf::RenderTarget* target);
	// Events
	void handle_click(const sf::Event::MouseButtonPressed* evt);
	void handle_mousemove(const sf::Event::MouseMoved* evt);
};
