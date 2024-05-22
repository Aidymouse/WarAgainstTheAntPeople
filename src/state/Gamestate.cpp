#include "include/Lib/Gamestate.h"
#include "include/Entities/Entity.h"
#include "include/Lib/CollisionGrid.h"

#include <memory>
#include <vector>

std::vector<std::shared_ptr<Entity>> Gamestate::entities;
CollisionGrid Gamestate::main_grid = CollisionGrid(64);

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
