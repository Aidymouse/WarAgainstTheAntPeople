#include <engine/Components.hpp>
#include <systems/PersuingSystem.h>

void PersuingSystem::update(float dt) {
	for (auto e=registered_entities.begin(); e != registered_entities.end(); e++) {
		Entity ent = (Entity) *e;
		Persuing p = component_manager->get_component_data<Persuing>(ent);

		std::cout << "Entity " << ent << " is persuing " << p.desiredX << ", " << p.desiredY << std::endl;
	}
}

