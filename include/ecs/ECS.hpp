#pragma once

#include "ecs/ComponentManager.hpp"
#include "ecs/SystemManager.hpp"
#include <boost/unordered/unordered_map_fwd.hpp>
#include <ecs/Entity.hpp>
#include <memory>
#include <queue>

#include <ProjectConfig.h>

class ECS {
	std::queue<Entity> free_ids;
	Entity num_entities = 0; 
	boost::unordered_map<Entity, Signature> signatures;
	
	std::shared_ptr<ComponentManager> component_manager = std::make_shared<ComponentManager>();
	std::shared_ptr<SystemManager> system_manager = std::make_shared<SystemManager>(component_manager);

public:
	ECS() {
		for (int e=0; e<MAX_ENTITIES; e++) {
			free_ids.push(e);
		}
	};

	Entity add_entity() {
		Entity id = free_ids.front();
		signatures[id] = 0;
		/*system_manager->entity_changed(num_entities, signature);*/
		free_ids.pop();
		num_entities++;
		return num_entities-1;
	};

	void remove_entity(Entity id) {
		signatures[id] = 0;
		component_manager->entity_removed(id);
		/*system_manager->entity_changed(id, signatures[id]);*/
		num_entities--;
		free_ids.push(id);
	};


	// Components
	template <typename T> void register_component() {
		component_manager->add_component<T>();
	}

	template <typename T> void add_component_to_entity(Entity id, T data) {
		int sig_index = component_manager->get_signature_index_for_type<T>();
		std::cout << "Adding entity " << id << " to component " << sig_index << std::endl;
		if (signatures[id][sig_index]) {
			std::cout << "Entity " << id << " already has " << typeid(T).name() << std::endl;
		} else {
			component_manager->get_component_array<T>()->add_entity(id, data);
			signatures[id][sig_index] = 1;
			system_manager->entity_changed(id, signatures[id]);
		}
	}

	template <typename T> void remove_component_from_entity(Entity id) {
		int sig_index = component_manager->get_signature_index_for_type<T>();
		if (not signatures[id][sig_index]) {
			std::cout << "Entity " << id << " does not have " << typeid(T).name() << ", so it will not be removed" << std::endl;
		} else {
			component_manager->get_component_array<T>()->remove_entity(id);
			signatures[id][sig_index] = 0;
			system_manager->entity_changed(id, signatures[id]);
		}
	}

	// System
	template <typename T> std::shared_ptr<T> register_system(Signature signature) {
		return system_manager->add_system<T>(signature);
	}
};
