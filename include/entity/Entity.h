#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Entity {
	int x;
	int y;
	unsigned short animation_frame;

protected:
	sf::Sprite sprite;

public:
	Entity(const sf::Texture* texture);
	sf::Sprite get_sprite() { return sprite; };
};

