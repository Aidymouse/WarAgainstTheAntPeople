#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

struct Position {
	int x;
	int y;
};

struct Translate {
	int vel_x;
	int vel_y;
};

struct Visible {
	std::shared_ptr<sf::Sprite> sprite;
	//long floob;
};
