#include <SFML/Graphics.hpp>

#include <iostream>

#pragma once
class Tool {
public:
	Tool() {};
	Tool(std::string filename);
	Tool(std::string filename, float offset_x, float offset_y);
	sf::Texture tex;
	sf::Sprite sprite;
	float sprite_origin_x = 0;
	float sprite_origin_y = 0;
	virtual void update(float dt, sf::RenderWindow* window);
	virtual void draw(sf::RenderWindow* window);
	virtual	void handle_event(sf::Event* event) {};
};
