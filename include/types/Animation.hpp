#pragma once

#include <SFML/Graphics.hpp>


struct animation {
	sf::IntRect texture_rectangle;
	float duration;
	animation* next_anim;
	int origin_x;
	int origin_y;
};
