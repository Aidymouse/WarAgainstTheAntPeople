#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <ecs/System.hpp>

class ToolClick : public System {
public:
	void handle_click(const sf::Event::MouseButtonPressed* evt);
	void update(float dt);
};
