#pragma once

#include <state/Gamestate.hpp>
#include <entities/Entity.hpp>
#include <state/CollisionGrid.hpp>
#include <entities/tools/ToolHolder.hpp>
#include <entities/creatures/Guy.hpp>

#include <memory>
#include <vector>

//Guy g = Guy(0, 0);

std::vector<std::shared_ptr<Entity>> Gamestate::entities;
//ToolHolder Gamestate::tool_holder;
CollisionGrid Gamestate::main_grid = CollisionGrid(64);
sf::Vector2i Gamestate::mouse_pos;

std::shared_ptr<Entity> Gamestate::insert_entity(std::shared_ptr<Entity> ent) {

  entities.emplace_back(ent);
  if (!ent->decoration) {
    main_grid.insert_entity(ent);
  }
  return ent;
};

void Gamestate::remove_marked_entities() {

  for (int i = entities.size() - 1; i >= 0; i--) {
    if (entities[i]->marked_for_deletion) {
      remove_entity(entities[i], i);
    }
  }

}

void Gamestate::remove_entity(std::shared_ptr<Entity> ent, int ent_index) {
  main_grid.remove_entity(ent);
  entities.erase(entities.begin() + ent_index);
}

