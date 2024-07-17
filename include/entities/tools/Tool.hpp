#pragma once

#include <entities/Entity.hpp>
#include <SFML/System.hpp>
#include <memory>

class Tool : public Entity {
public:
	Tool(float x, float y) : Entity::Entity(x, y) {};
	bool equipped = false;
	virtual void pick_up(){};
	virtual void set_down(){};
	virtual void activate(){};
	virtual void handle_event(sf::Event *event){};
};
