#include <iostream>
#include <ecs/Components.hpp>
#include <systems/PhysicsSystem.h>

void PhysicsSystem::update(float dt) {
	std::cout << "Physics System Update" << std::endl;
	for (auto e=registered_entities.begin(); e != registered_entities.end(); e++) {
		Entity ent = (Entity) *e;

		Position* p = component_manager->get_editable_component_data<Position>(ent);
		Translate t = component_manager->get_component_data<Translate>(ent);


		std::cout << ent << " (" << p->x << ", " << p->y << ") -> (" << p->x+t.vel_x << ", " << p->y+t.vel_y << ")" << std::endl;

		p->x += t.vel_x;
		p->y += t.vel_y;
	}
}
