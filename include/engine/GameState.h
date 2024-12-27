#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
class GameState {
public:

	virtual void load() = 0;
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderTarget* draw_target) = 0;
};
