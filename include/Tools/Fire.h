#include "Tools/Tool.h"

#include <SFML/Audio.hpp>

#pragma once
class Fire : public Tool {
public:
	Fire(std::string tex_filename, float origin_x, float origin_y);
	void draw(sf::RenderWindow* window) override;
	void handle_event(sf::Event* event) override;
};
