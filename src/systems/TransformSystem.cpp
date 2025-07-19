#include "components/Components.hpp"
#include "engine/CollisionGrid.h"
#include <systems/TransformSystem.h>

void TransformSystem::update(float dt, CollisionGrid *grid, ECS *ecs) {

	for (auto e = registered_entities.begin(); e != registered_entities.end(); e++) {
		Entity ent = (Entity)*e;
		Position *pos = component_manager->get_component_data<Position>(ent);
		Transform *trans = component_manager->get_component_data<Transform>(ent);

	float speed_multiplier = 1;

	/** Adjust speed multiplier based on amount carrying */
	if (ecs->entity_has_component<Carryable>(ent)) {
		Carryable c = *ecs->get_component_for_entity<Carryable>(ent);
		if (c.carrier_effort < c.min_weight) {
			//speed_multiplier = 0.05; // TODO
		} else {
			speed_multiplier = std::min((float)c.carrier_effort / (float)c.weight, 1.f);
		}

		//std::cout << "Speed Multiplier [" << ent << "]: " << speed_multiplier << std::endl;
	}

	pos->x += trans->vel_x * speed_multiplier * dt;
	pos->y += trans->vel_y * speed_multiplier * dt;

	//std::cout << "Trans [" << ent << "] " << trans->vel_x << ", " << trans->vel_y << std::endl;

	if (ecs->entity_has_component<Collider>(ent)) {
		Collider *c = component_manager->get_component_data<Collider>(ent);
		// std::cout << "Collider for " << ent << ", " << c << std::endl;

		Collisions::update_collider_position(c, pos->x, pos->y);

		grid->update_entity(ent, *pos, *c);
	}

	// If we were gonna do acceleration or anything we do it here
	}
};
