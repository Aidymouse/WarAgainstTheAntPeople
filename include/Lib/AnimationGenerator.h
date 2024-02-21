#include <SFML/Graphics.hpp>
#include <vector>

#pragma once
class AnimationGenerator {
public:
	static std::vector<sf::IntRect> generate_texture_rects(int sheet_width, int sheet_height, int frame_width, int frame_height);
};