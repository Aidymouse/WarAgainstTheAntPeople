#include "include/Lib/CollisionGrid.h"
#include "include/Entities/Entity.h"
#include <string>

CollisionGrid::CollisionGrid(int cell_size) { this->cell_size = cell_size; }

void CollisionGrid::insert_entity(std::shared_ptr<Entity> ent) {

  // std::cout << ent->pos.x << std::endl;

  int cell_col = ent->pos.x / cell_size;
  int cell_row = ent->pos.y / cell_size;

  std::string cell_id =
      std::to_string(cell_row) + ":" + std::to_string(cell_col);

  cells[cell_id].push_back(ent);
}

std::vector<grid_cell *> CollisionGrid::get_cells_within(float distance,
                                                         float x, float y) {

  int dist_to_top = (int)y % cell_size;
  int cells_up = (distance - dist_to_top) / cell_size + 1;

  int dist_to_bottom = cell_size - dist_to_top;

  int cells_down = (distance - dist_to_bottom) / cell_size + 1;

  int dist_to_left = int(x) % cell_size;
  int cells_left = (distance - dist_to_left) / cell_size + 1;

  int dist_to_right = cell_size - dist_to_left;
  int cells_right = (distance - dist_to_right) / cell_size + 1;

  int cell_col = x / cell_size;
  int cell_row = y / cell_size;

  // std::cout << dist_to_top << ", " << dist_to_bottom << ", " << dist_to_left
  // << ", " << dist_to_right << std::endl; std::cout << cells_up << ", " <<
  // cells_down << ", " << cells_left << ", " << cells_right << std::endl;

  std::vector<grid_cell *> retrieved_cells;

  for (int row = cell_row - cells_up; row <= (cell_row + cells_down); row++) {
    for (int col = cell_col - cells_left; col <= (cell_col + cells_right);
         col++) {

      std::string cell_id = std::to_string(row) + ":" + std::to_string(col);

      // We only want cells that actually exist
      grid_cell *cell;
      try {
        cell = &(cells.at(cell_id));
      } catch (std::out_of_range e) {
        continue;
      }

      retrieved_cells.emplace_back(cell);
    }
  }

  return retrieved_cells;
}

void CollisionGrid::remove_entity(std::shared_ptr<Entity> ent) {
  int cell_col = ent->pos.x / cell_size;
  int cell_row = ent->pos.y / cell_size;

  std::string cell_id =
      std::to_string(cell_row) + ":" + std::to_string(cell_col);

  grid_cell *cell = &cells[cell_id];
  for (int i = cell->size() - 1; i >= 0; i--) {
    if ((*cell)[i] == ent) {
      cell->erase(cell->begin() + i);
      return;
    }
  }
}

void CollisionGrid::draw() {}
