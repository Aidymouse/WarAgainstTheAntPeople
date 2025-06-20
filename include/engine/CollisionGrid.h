#pragma once

#include "components/Components.hpp"
#include "engine/Collisions.h"
#include <ecs/ECS.hpp>
#include <ecs/Entity.hpp>
#include <set>
#include <unordered_map>

typedef int collision_cell_id; // First 4 bits = row, second 4 = col
typedef std::set<Entity> collision_cell;
#define COLLISION_CELL_SIZE 100

class CollisionGrid {
  std::unordered_map<collision_cell_id, collision_cell> cells;
  std::unordered_map<Entity, std::set<collision_cell_id>> inhabited_cells;
  std::set<collision_cell_id> registered_cells;

public:
  CollisionGrid();

  void debug_cout_cell(collision_cell_id id);
  void debug_display();
  void debug_draw_grid(SDL_Renderer *renderer);

  void update_entity(Entity ent, Position pos, Collider col);
  std::set<collision_cell_id> get_overlapping_cells(Collider col);
  std::set<collision_cell_id> get_cells_for_entity(Entity ent);
  std::set<Entity> test_entity_for_collisions(Entity ent, ECS *ecs);
  std::set<Entity> get_collisions(Collider col, ECS *ecs);
};
