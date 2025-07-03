#pragma once

#include <ecs/ComponentManager.hpp>
#include <ecs/Entity.hpp>
#include <memory>
#include <set>

class System {
public:
  std::set<Entity> registered_entities;
  std::shared_ptr<ComponentManager> component_manager;

  void register_entity(Entity id) { registered_entities.insert(id); }

	void remove_entity(Entity id) { 
		registered_entities.erase(id);
 	}

  void set_component_manager(std::shared_ptr<ComponentManager> manager) {
    component_manager = manager;
  }

	void debug_cout_entities() {

		std::cout << registered_entities.empty();
/*
		int num_ents = registered_entities.size();
		std::cout << "System has " << num_ents << " entities ";
		if (num_ents > 0) {
			for (auto e = registered_entities.begin(); e != registered_entities.end(); e++) {
				Entity ent = (Entity) *e;
				std::cout << "[" << ent << "] ";
			}
		}
*/
		std::cout << std::endl;


	}
};
