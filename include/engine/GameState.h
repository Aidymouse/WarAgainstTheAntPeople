#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
class GameState {
public:
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderTarget* target) = 0;

	virtual void handle_click(const sf::Event::MouseButtonPressed*) {};
	virtual void handle_mousemove(const sf::Event::MouseMoved*) {};

	virtual void leave_state() = 0;
	virtual void enter_state() = 0;
};
