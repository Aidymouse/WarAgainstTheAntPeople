#include <systems/StapledToSystem.h>
#include <components/Components.hpp>

void StapledToSystem::update(float dt, ECS *ecs) {
	for (auto e=registered_entities.begin(); e!=registered_entities.end(); e++) {
	
		Entity ent = (Entity)*e;

		StapledTo stapled_to = *ecs->get_component_for_entity<StapledTo>(ent);

		if (!ecs->entity_has_component<Position>(stapled_to.entity)) {
			std::cout << "[" << ent << "] is stapled to [" << stapled_to.entity << "] but it does not have position" << std::endl;
			continue;
		}

		Position match_pos = *ecs->get_component_for_entity<Position>(stapled_to.entity);
		Position *stapled_pos = ecs->get_component_for_entity<Position>(ent);
		stapled_pos->x = match_pos.x+stapled_to.offset.x;
		stapled_pos->y = match_pos.y+stapled_to.offset.y;
		stapled_pos->z = match_pos.z;
		
	}
}
