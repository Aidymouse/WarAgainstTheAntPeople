#pragma once

#include <SFML/Graphics/Sprite.hpp>

class Entity {
	int x;
	int y;
	unsigned short animation_frame;
	sf::Sprite sprite;
};

class Tool : public Entity {
	int grabbed_by; // Guy id
	
public:
	void get_grabbed(int guy_id);
	void get_put_down();
	void activate();
};
