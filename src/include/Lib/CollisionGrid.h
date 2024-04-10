#include "../Entities/Entity.h"
#include <map>
#include <vector>

#pragma once
typedef std::vector<std::shared_ptr<Entity>> grid_cell;

class CollisionGrid {

public:
  CollisionGrid(int cell_size);
  int cell_size;
  std::map<std::string, grid_cell> cells;
  void insert_entity(std::shared_ptr<Entity> ent);
  std::vector<grid_cell *> get_cells_within(float distance, float x, float y,
                                            int extension = 0);
  void remove_entity(std::shared_ptr<Entity> ent);
  void update_entity(std::shared_ptr<Entity> ent);
  void draw();
};
