#include "Tools/Tool.h"
#include <SFML/Graphics.hpp>


Tool::Tool(std::string filename) {
	tex.loadFromFile(filename);

	sprite.setTexture(tex);
}

Tool::Tool(std::string filename, float origin_x, float origin_y) : Tool::Tool(filename) {
	sprite_origin_x = origin_x;
	sprite_origin_y = origin_y;
}

void Tool::update(float dt, sf::RenderWindow* window) {
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
	sprite.setPosition(mouse_pos.x - sprite_origin_x, mouse_pos.y - sprite_origin_y);
}

void Tool::draw(sf::RenderWindow* window) {
	window->draw(sprite);
}
