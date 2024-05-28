#include <entities/Entity.hpp>
#include <SFML/System.hpp>

#pragma once
class Tool : public Entity {
public:
	Tool(float x, float y);
	bool equipped = false;
	virtual void pick_up(){};
	virtual void set_down(){};
	virtual void handle_event(sf::Event *event){};
};
