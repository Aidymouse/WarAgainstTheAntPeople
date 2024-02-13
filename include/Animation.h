#include <SFML/Graphics.hpp>

#pragma once

struct animation {
	sf::IntRect texture_rectangle;
	float duration;
	animation* next_anim;
	int origin_x;
	int origin_y;
};
