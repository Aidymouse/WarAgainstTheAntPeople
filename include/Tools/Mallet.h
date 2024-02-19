#include "Tools/Tool.h"

#include <SFML/Audio.hpp>

#pragma once
class Mallet : public Tool {
public:
	Mallet(std::string tex_filename, float origin_x, float origin_y);
	sf::Sound sound;
	void draw(sf::RenderWindow* window) override;
	void handle_event(sf::Event* event) override;
};
