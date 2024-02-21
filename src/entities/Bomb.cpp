#include <SFML/Graphics.hpp>
#include <iostream>

#include "Types/Animation.h"
#include "Lib/Helper.hpp"
#include "Lib/Gamestate.h"
#include "Lib/AnimationGenerator.h"

#include "Entities/Entity.h"
#include "Entities/Bomb.h"


const std::vector<sf::IntRect> bomb_graphics_rects = AnimationGenerator::generate_texture_rects(64, 64, 16, 16);

struct {
	animation bomb1 = { bomb_graphics_rects[1], MAX_FUSE_TIMER / 8, & bomb2, 8, 8};
	animation bomb2 = { bomb_graphics_rects[2], MAX_FUSE_TIMER / 8, &bomb3, 8, 8};
	animation bomb3 = { bomb_graphics_rects[3], MAX_FUSE_TIMER/8, &bomb4, 8, 8 };
	animation bomb4 = { bomb_graphics_rects[4], MAX_FUSE_TIMER/8, &bomb5, 8, 8 };
	animation bomb5 = { bomb_graphics_rects[5], MAX_FUSE_TIMER/8, &bomb6, 8, 8 };
	animation bomb6 = { bomb_graphics_rects[6], MAX_FUSE_TIMER / 8, &bomb7, 8, 8};
	animation bomb7 = { bomb_graphics_rects[7], MAX_FUSE_TIMER/8, &bomb8, 8, 8 };
	animation bomb8 = { bomb_graphics_rects[8], MAX_FUSE_TIMER/8, &explode1, 8, 8 };

	animation explode1 = { bomb_graphics_rects[9], 0.05, &explode2, 8, 8};
	animation explode2 = { bomb_graphics_rects[10], 0.05, &explode3, 8, 8 };
	animation explode3 = { bomb_graphics_rects[11], 0.05, &explode4, 8, 8 };
	animation explode4 = { bomb_graphics_rects[12], -1, NULL, 8, 8 };
} bomb_anims;


Bomb::Bomb(sf::Texture* tex, float x, float y) : Entity::Entity(x,y) {
	this->tex = tex;
	sprite.setTexture(*tex);

	init_animation(&bomb_anims.bomb1);

}

void Bomb::update(float dt) {

	update_animation(dt);

	sprite.setPosition(pos.x-cur_anim->origin_x, pos.y-cur_anim->origin_y);

	timer -= dt;
	lifetime -= dt;

	if (timer <= 0 && !exploded) {
		exploded = true;

		std::vector<grid_cell*> exploded_cells = Gamestate::main_grid.get_cells_within(EXPLOSION_RADIUS, pos.x, pos.y);

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

	}

	if (lifetime <= 0) {
		marked_for_deletion = true;
	}

}


void Bomb::draw(sf::RenderWindow* window) {
	window->draw(sprite);

}

void Bomb::say_type() {
	std::cout << "Bomb" << std::endl;
}
