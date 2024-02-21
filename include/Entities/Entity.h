#include <SFML/Graphics.hpp>

#include "Types/Animation.h"
#include "Types/Collisions.h"

#pragma once
class Entity
{
public:
	Entity() = default;
	Entity(float x, float y);
	sf::Vector3<float> pos;
	sf::Vector3<float> pos_at_frame_start;
	bool decoration = false;
	bool marked_for_deletion = false;
	virtual void update(float dt) {};
	virtual void draw(sf::RenderWindow* window) {};
	virtual void say_type();
	virtual void handle_collision(Collision collision) {};

	sf::Texture tex;
	sf::Sprite sprite;
	animation* cur_anim = NULL;
	float animation_timer = 0;
	virtual void update_animation(float dt);
	virtual void init_animation(animation* anim);
	virtual void maintain_grid_pre_update();
	virtual void maintain_grid_post_update();
};