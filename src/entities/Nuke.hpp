#include <SFML/Graphics.hpp>
#include <iostream>

#include "Helper.h"
#include "../Gamestate.hpp"

#include "Entity.hpp"

const float GRAVITY = 100.0;
const int BOMB_RADIUS = 10;
const int EXPLOSION_RADIUS = 50;

// This comes from the sky and blasts a bunch of guys to heaven

#pragma once
class Bomb : public Entity {
public:
	sf::CircleShape ellipse;
	sf::Texture *tex;
	sf::Sprite sprite;
	Bomb(sf::Texture* tex, float x, float y);
	void update(float dt) override;
	void draw(sf::RenderWindow* window) override;
	void say_type() override;
};

Bomb::Bomb(sf::Texture* tex, float x, float y) : Entity::Entity(x,y) {
	this->tex = tex;
	sprite.setTexture(*tex);

	pos.z = 50;
	ellipse = sf::CircleShape(BOMB_RADIUS+pos.z);
	ellipse.setFillColor(sf::Color(150, 0, 0));
	ellipse.setPosition(pos.x-BOMB_RADIUS/2, pos.y-BOMB_RADIUS/2);
}

void Bomb::update(float dt) {
	pos.z = pos.z - GRAVITY * dt;
	ellipse.setRadius(BOMB_RADIUS + pos.z);
	ellipse.setPosition(pos.x - ellipse.getRadius() / 2, pos.y - ellipse.getRadius() / 2 - pos.z);

	sprite.setPosition(pos.x, pos.y - pos.z);

	sprite.setScale(pos.z, pos.z);

	if (pos.z <= 0) {
		Gamestate& gamestate = Gamestate::getInstance();
		std::vector<grid_cell*> exploded_cells = gamestate.main_grid.get_cells_within(EXPLOSION_RADIUS, pos.x, pos.y);

		for (auto &cell : exploded_cells) {
			for (auto& entity : *cell) {
				float dist = Helper::dist_tween_points(entity->pos.x, entity->pos.y, pos.x, pos.y);
				if (dist <= EXPLOSION_RADIUS) {
					Collision col;
					col.type = Collisions::EXPLOSION;
					col.data.explosion.distance = dist;
					
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
