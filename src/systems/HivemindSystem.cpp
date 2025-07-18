#include "engine/CollisionGrid.h"
#include <components/HivemindComponents.hpp>
#include <exception>
#include <systems/HivemindBrainSystem.h>

void hv_handle_collisions(float dt, ECS *ecs, CollisionGrid *grid);
// TODO
void hv_strip_nonexistant_participants(float dt, ECS *ecs);

void HivemindBrainSystem::update(float dt, ECS *ecs, CollisionGrid *grid) {

	hv_strip_nonexistant_participants(dt, ecs);

	std::shared_ptr<ComponentArray<hv_Brain>> comp_brains = ecs->get_component_array<hv_Brain>();

	for (int h = 0; h < comp_brains->get_num_components(); h++) {

		/** Keep all the hiveminds children synced with this */
		Entity hv_entity = comp_brains->get_entity_from_idx(h);
		hv_Brain brain = comp_brains->get_data_from_idx(h);
		Position *hv_pos = ecs->get_component_for_entity<Position>(hv_entity);

		for (int ent_idx = 0; ent_idx < brain.num_entities; ent_idx++) {
			Entity attached_ent = brain.entities[ent_idx];

			Position *p = ecs->get_component_for_entity<Position>(attached_ent);
			hv_Participant *hv_info = ecs->get_component_for_entity<hv_Participant>(attached_ent);

			p->x = hv_pos->x + hv_info->offset.x;
			p->y = hv_pos->y + hv_info->offset.y;

			//std::cout << "[" << hv_entity << "] participant [" << attached_ent << "] new position: (" << p->x << ", " << p->y << ")" << std::endl;
		}
	}

	//hv_handle_collisions(dt, ecs, grid);
}

/*
void hv_handle_collisions(float dt, ECS *ecs, CollisionGrid *grid) {
	std::shared_ptr<ComponentArray<hv_Brain>> comp_brains =
			ecs->get_component_array<hv_Brain>();

	for (int h = 0; h < comp_brains->get_num_components(); h++) {
	}
}
*/

void hv_strip_nonexistant_participants(float dt, ECS *ecs) {
	std::shared_ptr<ComponentArray<hv_Brain>> comp_hv_brains = ecs->get_component_array<hv_Brain>();

	for (int b = 0; b < comp_hv_brains->get_num_components(); b++) {
		Entity hv_Ent = comp_hv_brains->get_entity_from_idx(b);

		hv_Brain *brain = comp_hv_brains->get_editable_data_from_idx(b);

		for (int e = 0; e < brain->num_entities; e++) {
			Entity participant_ent = brain->entities[e];

			// ecs->debug_cout_entity_state(participant_ent);
			// throw std::exception();
			if (!ecs->entity_exists(participant_ent)) {
				// std::cout << "[" << hv_Ent << "] participant [" << participant_ent << "] does not exist!" << std::endl;
				Entity latest = brain->entities[brain->num_entities - 1];
				brain->entities[e] = latest;
				brain->entities[brain->num_entities - 1] = -1;
				brain->num_entities--;
				e--;
			}
		}
	}
}

