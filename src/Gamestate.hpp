#include <vector>
#include <memory>

#include "entities/Entity.hpp"
#include "CollisionGrid.hpp"

#include <iostream>

#pragma once
class Gamestate {
public:
	static Gamestate& getInstance() {
		static Gamestate instance;
		return instance;
	}
	
	std::vector<std::shared_ptr<Entity>> entities;
	CollisionGrid main_grid = CollisionGrid(50);

	std::shared_ptr<Entity> insert_entity(std::shared_ptr<Entity> ent) {
		entities.emplace_back(ent);
		if (!ent->decoration) {
			main_grid.insert_entity(ent);
		}
		return ent;
	};

	void remove_marked_entities() {

		
		for (int i = entities.size()-1; i >= 0; i--) {
			if (entities[i]->marked_for_deletion) {
				remove_entity(entities[i], i);
			}
		}
		
	}

	void remove_entity(std::shared_ptr<Entity> ent, int ent_index) {
		main_grid.remove_entity(ent);
		entities.erase(entities.begin() + ent_index);
	}

private:
	Gamestate() = default;
	Gamestate(const Gamestate&) = delete;
	Gamestate& operator=(const Gamestate&) = delete;
};