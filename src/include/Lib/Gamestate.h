#include "../Lib/CollisionGrid.h"
#include <vector>

#pragma once
class Gamestate {
public:
  static std::vector<std::shared_ptr<Entity>> entities;
  static CollisionGrid main_grid;

  static std::shared_ptr<Entity> insert_entity(std::shared_ptr<Entity> ent, bool debug = false);
  static void remove_marked_entities();
  static void remove_entity(std::shared_ptr<Entity> ent, int ent_index);
};
