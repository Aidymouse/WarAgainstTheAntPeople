#include "Entities/Entity.h"
#include "Lib/Helper.hpp"

#pragma once
struct timers {
	float animation = 0;
};

class Guy : public Entity
{
public:
	sf::Sprite sprite;
	sf::Texture *tex;

	timers timers;

	animation* cur_anim;

	float sound_timer = Helper::random(1, 30);

	float spazz_mult;

	sf::Vector3<float> ground_vel_dir;
	float ground_velocity = 0;

	float z_vel = 0;

	float gravity_strength = 20;

	Guy(sf::Texture *tex, float x, float y);
	void update(float dt) override;
	void draw(sf::RenderWindow *window) override;
	void say_type() override;
	void handle_collision(Collision collision) override;
};
