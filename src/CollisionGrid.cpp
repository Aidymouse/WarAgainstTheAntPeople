#include "include/Lib/CollisionGrid.h"
#include "include/Entities/Entity.h"
#include "include/Lib/CollisionManager.h"
#include "include/Types/CollisionShapes.h"
#include <iostream>
#include <string>

CollisionGrid::CollisionGrid(int cell_size) { this->cell_size = cell_size; }

std::string row_col_to_id(int row, int col) { 
  return std::to_string(row) + ":" + std::to_string(col);
}

struct cell_pos {
  int row;
  int col;
};

cell_pos id_to_row_col(std::string cell_id) {
    cell_pos pos;
    pos.row = std::stoi(cell_id.substr(0, cell_id.find(":")));
    pos.col = std::stoi(cell_id.substr(cell_id.find(":") + 1, cell_id.length()));
    return pos;
}

void CollisionGrid::insert_entity(std::shared_ptr<Entity> ent, bool debug) {

  std::vector<std::string> inhabited_ids;

  int base_cell_col = ent->pos.x / cell_size;
  int base_cell_row = ent->pos.y / cell_size;
  std::string base_cell_id = row_col_to_id(base_cell_row, base_cell_col);

  // If it's a rectangle, we wanna check cells left and down
  int cells_right;
  int cells_down;
  int row_mod_start = 0;
  int col_mod_start = 0;

  // TODO: Need to find current distance to right edge of base cell
  if (ent->collider.type == CollisionShapeType::RECT) {
    cells_right = cell_size / ent->collider.collisionShape.rect.width + 1;
    cells_down = cell_size / ent->collider.collisionShape.rect.height + 1;

  } else if (ent->collider.type == CollisionShapeType::CIRCLE) {

    cells_right =
        cell_size / (ent->collider.collisionShape.circle.radius * 2) + 1;
    cells_down =
        cell_size / (ent->collider.collisionShape.circle.radius * 2) + 1;
    col_mod_start = -cells_right / 2;
    row_mod_start = -cells_down / 2;
  } else {

  }

  for (int row_mod = row_mod_start; row_mod < cells_down; row_mod++) {
    for (int col_mod = col_mod_start; col_mod < cells_right; col_mod++) {
      Collider check_cell_collider;
      check_cell_collider.type = CollisionShapeType::RECT;
      check_cell_collider.x = (base_cell_col + col_mod) * cell_size;
      check_cell_collider.y = (base_cell_row + row_mod) * cell_size;
      check_cell_collider.collisionShape.rect.height = cell_size;
      check_cell_collider.collisionShape.rect.width = cell_size;

      if (CollisionManager::does_collide(&check_cell_collider, &ent->collider)) {
        std::string cell_id = row_col_to_id(base_cell_row+row_mod, base_cell_col + col_mod);
        inhabited_ids.push_back(cell_id);
        cells[cell_id].push_back(ent);
      }
    }
  }

  ent->update_collision_cells(inhabited_ids);
  if (debug) {
    std::cout << "Inhabited ids for this entity: ";
    for (auto const id : inhabited_ids) {
      std::cout<< id << ", ";
    }
    std::cout << std::endl;
  }
}

std::vector<grid_cell *> CollisionGrid::get_cells_within(float distance,
                                                         float x, float y,
                                                         int extension) {

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

  for (int row = cell_row - cells_up - extension;
       row <= (cell_row + cells_down + extension); row++) {
    for (int col = cell_col - cells_left - extension;
         col <= (cell_col + cells_right + extension); col++) {

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

  std::string cell_id = row_col_to_id(cell_row, cell_col);

  grid_cell *cell = &cells[cell_id];
  for (int i = cell->size() - 1; i >= 0; i--) {
    if ((*cell)[i] == ent) {
      cell->erase(cell->begin() + i);
      return;
    }
  }
}

void CollisionGrid::update_entity(std::shared_ptr<Entity> ent) {}

void CollisionGrid::draw(sf::RenderWindow *window) {
  for (auto const &cell_info : cells) {
    std::string cell_id = cell_info.first;


    cell_pos p = id_to_row_col(cell_id);
    int cell_col = p.col;
    int cell_row = p.row;

    sf::RectangleShape cell_rect(sf::Vector2f(cell_size, cell_size));
    cell_rect.setPosition(
        sf::Vector2f(cell_col * cell_size, cell_row * cell_size));
    cell_rect.setFillColor(sf::Color(0, 0, 0, 0));
    cell_rect.setOutlineColor(sf::Color(255, 0, 0, 128));
    cell_rect.setOutlineThickness(1);

    window->draw(cell_rect);
  }
}
