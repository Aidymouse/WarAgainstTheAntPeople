#include <state/CollisionGrid.hpp>
#include <entities/tools/Tool.hpp>
#include <vector>

#pragma once
class Gamestate {
public:
  static std::vector<std::shared_ptr<Entity>> entities;
  static CollisionGrid main_grid;
  static std::shared_ptr<Tool> equipped_tool;

  static std::shared_ptr<Entity> insert_entity(std::shared_ptr<Entity> ent);
  static void remove_marked_entities();
  static void remove_entity(std::shared_ptr<Entity> ent, int ent_index);
};
