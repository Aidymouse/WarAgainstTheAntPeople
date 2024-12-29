#pragma once

#include <entity/Entity.h>
#include <entity/Guy.h>

struct Guy;

class Tool : public Entity {
	Guy* grabbed_by = nullptr; // Guy id
		
public:
	Tool(const sf::Texture* texture);
	void get_grabbed(int guy_id);
	void get_put_down();
	void activate();
};
