#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Entity {

protected:
	sf::Sprite sprite;
	int x;
	int y;
	unsigned short animation_frame;
	int collision_cell_idx = -1;

public:
	Entity(const sf::Texture* texture);
	sf::Sprite get_sprite() { return sprite; };
};

