#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
class GameState {
public:
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderTarget* target) = 0;
	virtual void leave_state() = 0;
	virtual void enter_state() = 0;
};
