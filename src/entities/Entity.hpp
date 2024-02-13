#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "Animation.h"

struct explosion_collision {
	float distance;
	float bomb_pos_x;
	float bomb_pos_y;
};

union collision_data {
	explosion_collision explosion;
};

enum Collisions {
	MALLET,
	EXPLOSION
};


class Entity;

struct Collision {
	Collisions type;
	Entity* collided_with;
	collision_data data;
};

#pragma once
class Entity
{
public:
	Entity() = default;
	Entity(float x, float y);
	sf::Vector3<float> pos;
	bool decoration = false;
	bool marked_for_deletion = false;
	virtual void update(float dt) {};
	virtual void draw(sf::RenderWindow* window) {};
	virtual void say_type();
	virtual void handle_collision(Collision collision) {};

	sf::Sprite sprite;
	animation* cur_anim = NULL;
	float animation_timer = 0;
	virtual void update_animation(float dt);
};


Entity::Entity(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void Entity::say_type() {
	std::cout << "Entity" << std::endl;
}

void Entity::update_animation(float dt) {
	if (cur_anim->next_anim == NULL) {
		return;
	}
	animation_timer -= dt;
	if (animation_timer <= 0) {
		cur_anim = cur_anim->next_anim;
		animation_timer = cur_anim->duration + animation_timer;
		sprite.setTextureRect(cur_anim->texture_rectangle);
	}
}