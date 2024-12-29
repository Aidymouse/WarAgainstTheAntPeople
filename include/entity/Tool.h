#pragma once

#include <SFML/System/Vector2.hpp>
#include <entity/Entity.h>
#include <entity/Guy.h>

struct Guy;

class Tool : public Entity {
	Guy* grabbed_by = nullptr; // Guy id
	bool grabbed_by_player = false;
		
public:
	Tool(const sf::Texture* texture);
	void get_grabbed(int guy_id);
	void get_put_down();
	void activate();
	virtual void handle_click() = 0;
	virtual void handle_mousemove(sf::Vector2i mouse_pos) = 0;
};
