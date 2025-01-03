#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

enum COMP_SIG { // Component Signature Indexes
	POSITION = 0,
	TRANSLATE = 1,
	VISIBLE = 2
};

struct Position {
	float x;
	float y;
};

struct Translate {
	int vel_x;
	int vel_y;
};

struct Visible {
	std::shared_ptr<sf::Sprite> sprite;
};
