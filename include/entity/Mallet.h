#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <entity/Tool.h>
#include <engine/Collisions.h>

class Mallet : public Tool {

public:
	Mallet();
	void set_position(int x, int y);
	CollisionShape get_collision_shape();
	void handle_click() override;
	void handle_mousemove(sf::Vector2i mouse_pos) override;

};
