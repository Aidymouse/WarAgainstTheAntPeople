#include <SFML/Graphics.hpp>

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Animation.h"
#include "Helper.h"
#include "../Gamestate.hpp"
#include "../AudioManager.hpp"

#include "Entity.hpp"
#include "decorations/Bloodstain.hpp"

static float speed = 100.0;

struct {
	const sf::IntRect g1 = sf::IntRect(0, 0, 16, 16);
	const sf::IntRect g2 = sf::IntRect(16, 0, 16, 16);
} guy_graphic_rects;

struct {
	animation g1 = { guy_graphic_rects.g1, 0.15, &g2, 8, 8 };
	animation g2 = { guy_graphic_rects.g2, 0.15, &g1, 8, 8 };
} guy_anims;

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

	float gravity_strength = 5;

	Guy(sf::Texture *tex, float x, float y);
	void update(float dt) override;
	void draw(sf::RenderWindow *window) override;
	void say_type() override;
	void handle_collision(Collision collision) override;
};

Guy::Guy(sf::Texture *t, float x, float y) : Entity::Entity(x, y) {
	tex = t;
	sprite.setTexture(*tex);
	sprite.setPosition(pos.x, pos.y);

	spazz_mult = (5 + rand() % 6) / 10.0;
	
	cur_anim = &(guy_anims.g1);

	timers.animation = cur_anim->duration;

	sprite.setTextureRect( (*cur_anim).texture_rectangle );


}

void Guy::update(float dt) {

	pos += ground_vel_dir * ground_velocity * dt;
	//pos.z += z_vel * dt;

	sound_timer -= dt;
	if (sound_timer <= 0) {
		int mumble_num = Helper::random(1, 3);
		AudioManager::play_sound("mumble" + std::to_string(mumble_num));
		sound_timer = Helper::random(20, 30);
	}
	// Update Animation
	timers.animation -= dt;
	if (timers.animation <= 0) {
		cur_anim = cur_anim->next_anim;
		timers.animation = cur_anim->duration * spazz_mult;
		sprite.setTextureRect(cur_anim->texture_rectangle);
	}
	
	// Shake em around
	if (cur_anim == &guy_anims.g1 || cur_anim == &guy_anims.g2) {
		sprite.setPosition(pos.x + (rand() % 2 - 1 ) - cur_anim->origin_x, pos.y + rand() % 2 - 1 - cur_anim->origin_y - pos.z);
	}


}

void Guy::draw(sf::RenderWindow* window) {
	window->draw(sprite);
}

void Guy::say_type() {
	std::cout << "Guy" << std::endl;
}

void Guy::handle_collision(Collision collision) {

	if (collision.type == Collisions::MALLET) {

		Gamestate& gamestate = Gamestate::getInstance();
		gamestate.insert_entity(std::shared_ptr<Bloodstain>(new Bloodstain(pos.x, pos.y)));
		marked_for_deletion = true;

	}

	if (collision.type == Collisions::EXPLOSION) {
		z_vel = collision.data.explosion.distance;
		sf::Vector2<float> bomb_pos(collision.data.explosion.bomb_pos_x, collision.data.explosion.bomb_pos_y);
		sf::Vector2 < float> pos_2d(pos.x, pos.y);
		sf::Vector2<float> to_bomb = pos_2d - bomb_pos;
		ground_vel_dir.x = to_bomb.x;
		ground_vel_dir.y = to_bomb.y;
		Helper::normalize_vec3(&ground_vel_dir);
		ground_velocity = 100;
	}

}