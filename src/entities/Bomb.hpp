#include <SFML/Graphics.hpp>
#include <iostream>

#include "Animation.h"
#include "Helper.h"
#include "../Gamestate.hpp"

#include "Entity.hpp"

const int BOMB_RADIUS = 10;
const int EXPLOSION_RADIUS = 50;
const float MAX_TIMER = 3;

struct {
	const sf::IntRect bomb1 = sf::IntRect(0, 0, 16, 16);
	const sf::IntRect bomb2 = sf::IntRect(16, 0, 16, 16);
	const sf::IntRect bomb3 = sf::IntRect(32, 0, 16, 16);
	const sf::IntRect bomb4 = sf::IntRect(48, 0, 16, 16);
	const sf::IntRect bomb5 = sf::IntRect(0, 16, 16, 16);
	const sf::IntRect bomb6 = sf::IntRect(16, 16, 16, 16);
	const sf::IntRect bomb7 = sf::IntRect(32, 16, 16, 16);
	const sf::IntRect bomb8 = sf::IntRect(48, 16, 16, 16);

	const sf::IntRect explode1 = sf::IntRect(32, 32, 16, 16);
	const sf::IntRect explode2 = sf::IntRect(48, 32, 16, 16);
	const sf::IntRect explode3 = sf::IntRect(0, 48, 16, 16);
	const sf::IntRect explode4 = sf::IntRect(16, 48, 16, 16);
} bomb_graphics_rects;

struct {
	animation bomb1 = { bomb_graphics_rects.bomb1, MAX_TIMER/8, &bomb2, 8, 8 };
	animation bomb2 = { bomb_graphics_rects.bomb2, MAX_TIMER/8, &bomb3, 8, 8 };
	animation bomb3 = { bomb_graphics_rects.bomb3, MAX_TIMER/8, &bomb4, 8, 8 };
	animation bomb4 = { bomb_graphics_rects.bomb4, MAX_TIMER/8, &bomb5, 8, 8 };
	animation bomb5 = { bomb_graphics_rects.bomb5, MAX_TIMER/8, &bomb6, 8, 8 };
	animation bomb6 = { bomb_graphics_rects.bomb6, MAX_TIMER/8, &bomb7, 8, 8 };
	animation bomb7 = { bomb_graphics_rects.bomb7, MAX_TIMER/8, &bomb8, 8, 8 };
	animation bomb8 = { bomb_graphics_rects.bomb8, MAX_TIMER/8, &explode1, 8, 8 };

	animation explode1 = { bomb_graphics_rects.explode1, 0.05, &explode2, 8, 8 };
	animation explode2 = { bomb_graphics_rects.explode2, 0.05, &explode3, 8, 8 };
	animation explode3 = { bomb_graphics_rects.explode3, 0.05, &explode4, 8, 8 };
	animation explode4 = { bomb_graphics_rects.explode4, -1, NULL, 8, 8 };
} bomb_anims;

#pragma once
class Bomb : public Entity {
public:
	sf::CircleShape ellipse;
	sf::Texture *tex;
	float timer = MAX_TIMER;
	Bomb(sf::Texture* tex, float x, float y);
	void update(float dt) override;
	void draw(sf::RenderWindow* window) override;
	void say_type() override;
};

Bomb::Bomb(sf::Texture* tex, float x, float y) : Entity::Entity(x,y) {
	this->tex = tex;
	sprite.setTexture(*tex);

	cur_anim = &bomb_anims.bomb1;
	sprite.setTextureRect(cur_anim->texture_rectangle);

}

void Bomb::update(float dt) {

	update_animation(dt);

	sprite.setPosition(pos.x-cur_anim->origin_x, pos.y-cur_anim->origin_y);

	std::cout << timer << std::endl;

	timer -= dt;

	if (timer <= 0) {
		Gamestate& gamestate = Gamestate::getInstance();
		std::vector<grid_cell*> exploded_cells = gamestate.main_grid.get_cells_within(EXPLOSION_RADIUS, pos.x, pos.y);

		for (auto &cell : exploded_cells) {
			for (auto& entity : *cell) {
				float dist = Helper::dist_tween_points(entity->pos.x, entity->pos.y, pos.x, pos.y);
				if (dist <= EXPLOSION_RADIUS) {
					Collision col;
					col.type = Collisions::EXPLOSION;
					col.data.explosion.distance = dist;
					col.data.explosion.bomb_pos_x = pos.x;
					col.data.explosion.bomb_pos_y = pos.y;
					
					entity->handle_collision(col);
				}
			}

		}

		marked_for_deletion = true;
	}

}


void Bomb::draw(sf::RenderWindow* window) {
	window->draw(sprite);

}

void Bomb::say_type() {
	std::cout << "Bomb" << std::endl;
}
