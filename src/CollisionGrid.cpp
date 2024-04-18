#include "include/Lib/CollisionGrid.h"
#include "include/Entities/Entity.h"
#include "include/Types/CollisionShapes.h"
#include <string>

CollisionGrid::CollisionGrid(int cell_size) { this->cell_size = cell_size; }

bool CollisionGrid::does_collide(Collider s1, Collider s2) {
  // Circle Circle
  if (s1.type == CollisionShapeType::CIRCLE &&
      s2.type == CollisionShapeType::CIRCLE) {
    return sqrt((s1.x - s2.x) * (s1.x - s2.x) +
                (s1.y - s2.y) * (s1.y - s2.y)) <=
           s1.collisionShape.circle.radius + s2.collisionShape.circle.radius;

    // Rect - Circle (primitavely treats circle as rectangle)
  } else if (s1.type == CollisionShapeType::CIRCLE &&
                 s2.type == CollisionShapeType::RECT ||
             s1.type == CollisionShapeType::RECT &&
                 s2.type == CollisionShapeType::CIRCLE) {

    Collider *circle = s1.type == CollisionShapeType::CIRCLE ? &s1 : &s2;
    Collider *rect = s1.type == CollisionShapeType::RECT ? &s1 : &s2;

    float rect_width = rect->collisionShape.square.width;
    float rect_height = rect->collisionShape.square.height;
    float circ_radius = circle->collisionShape.circle.radius;
    float circ_x = circle->x - circ_radius / 2;
    float circ_y = circle->y - circ_radius / 2;

    return (
        circ_x <= rect->x + rect_width && circ_x + circ_radius * 2 >= rect->x &&
        circ_y <= rect->y + rect_height && circ_y + circ_radius * 2 >= rect->y);

    // Rect - Rect
  } else if (s1.type == CollisionShapeType::RECT &&
             s2.type == CollisionShapeType::RECT) {
    float s1width = s1.collisionShape.square.width;
    float s1height = s1.collisionShape.square.height;
    float s2width = s2.collisionShape.square.width;
    float s2height = s2.collisionShape.square.height;
    return (s1.x <= s2.x + s2width && s1.x + s1width >= s2.x &&
            s1.y <= s2.y + s2height && s1.y + s1height >= s2.y);
  }
  return false;
}

void CollisionGrid::insert_entity(std::shared_ptr<Entity> ent) {

  // std::cout << ent->pos.x << std::endl;

  std::vector<std::string> inhabited_ids;
  // There probably needs to be some sort of provision for entities that span
  // multiple cells... or ones that overlap cell boundaries... Fuck
  int cell_col = ent->pos.x / cell_size;
  int cell_row = ent->pos.y / cell_size;

  std::string base_cell_id =
      std::to_string(cell_row) + ":" + std::to_string(cell_col);

  inhabited_ids.push_back(base_cell_id);

  cells[base_cell_id].push_back(ent);
  ent->update_collision_cells(inhabited_ids);
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

void CollisionGrid::update_entity(std::shared_ptr<Entity> ent) {}

void CollisionGrid::draw() {}
