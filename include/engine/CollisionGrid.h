#pragma once

#include "engine/Collisions.h"
#include "engine/Components.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <bitset>
#include <ecs/Entity.hpp>
#include <set>
#include <unordered_map>

typedef int collision_cell_id;
typedef std::set<Entity> collision_cell;
#define COLLISION_CELL_SIZE 100

class CollisionGrid {
  std::unordered_map<collision_cell_id, collision_cell> cells;
  std::unordered_map<Entity, std::set<collision_cell_id>> inhabited_cells;
  std::set<collision_cell_id> registered_cells;

public:
  CollisionGrid();

  void debug_draw_grid(sf::RenderTarget *target);

  void update_entity(Entity ent, Position pos);
  std::set<collision_cell_id> get_cells_overlapping(CollisionShape shape);
};
