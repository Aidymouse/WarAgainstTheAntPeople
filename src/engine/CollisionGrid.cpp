#include "SDL3/SDL_render.h"
#include "engine/Collisions.h"
#include "engine/Components.hpp"
#include <ProjectConfig.h>
#include <engine/CollisionGrid.h>
#include <iostream>
#include <util/Vec2.hpp>

collision_cell_id get_cell_id(int row, int col) { return (row << 4) + col; }
Vec2 get_cell_row_col(collision_cell_id id) {
  int row = id >> 4;
  int col = id - (row << 4);
  return Vec2(row, col);
}

void debug_cout_cell_id(collision_cell_id id) {
  Vec2 row_col = get_cell_row_col(id);
  std::cout << "Cell " << id << " (" << row_col.x << ", " << row_col.y << ") ";
}

CollisionGrid::CollisionGrid() {
  int cols = WINDOW_WIDTH / COLLISION_CELL_SIZE + 1;
  int rows = WINDOW_HEIGHT / COLLISION_CELL_SIZE + 1;

  for (int col = 0; col < cols; col++) {
    for (int row = 0; row < rows; row++) {
      collision_cell_id id = (row << 4) + col;

      registered_cells.insert(id);
    }
  }
}

// FOR NOW! Remove all cells then reapply all
void CollisionGrid::update_entity(Entity ent, Position pos, Collider col) {

  collision_cell_id prev = -1;

  collision_cell inhabited = inhabited_cells[ent];

  if (inhabited_cells[ent].size() > 0) {
    prev = (int)*inhabited_cells[ent].begin();
  }

  for (auto cell_iter = inhabited.begin(); cell_iter != inhabited.end();
       cell_iter++) {
    collision_cell_id cell_id = (collision_cell_id)*cell_iter;
    cells[cell_id].erase(ent);
  }

  inhabited_cells[ent].clear();
  // while (inhabited_cells[ent].size() > 0) {
  //  inhabited_cells[ent].erase(inhabited_cells.begin());
  // }
  // for (auto cell_iter = inhabited_cells[ent].end();
  //      cell_iter != inhabited_cells[ent].begin(); cell_iter--) {
  //   std::cout << "Erasing " << std::endl;
  //   collision_cell_id cell_id = (collision_cell_id)*cell_iter;
  //   prev = cell_id;
  //   // std::cout << "Erasing " << cell_id;
  //   inhabited_cells[ent].erase(cell_id);
  // }

  int init_col = pos.x / COLLISION_CELL_SIZE;
  int init_row = pos.y / COLLISION_CELL_SIZE;

  // std::set<collision_cell_id> in_cells;

  // TODO: Ability to be in more than one cell at once

  // std::cout << "Updating collision cell for ent " << ent << " at " << pos.x
  //           << ", " << pos.y << std::endl;
  // std::cout << "Init: " << init_col << ", " << init_row << std::endl;

  collision_cell_id new_id = get_cell_id(init_row, init_col);
  //
  // in_cells.insert(get_cell_id(init_row, init_col));
  inhabited_cells[ent].insert(new_id);
  cells[new_id].insert(ent);

  // if (new_id != prev && prev != -1) {
  //   std::cout << "Ent " << ent << " updated ColGrid from ";
  //   debug_cout_cell_id(prev);
  //   debug_cout_cell_id(new_id);
  //   std::cout << std::endl;
  //
  //   debug_cout_cell(new_id);
  // }
}

std::set<collision_cell_id> get_cells_overlapping(Collider col) {
  std::set<collision_cell_id> ids;

  if (col.type == CollisionShapeType::CIRCLE) {
    // TODO
  } else if (col.type == CollisionShapeType::RECT) {
    // TODO
  } else {
    std::cout << "Invalid collider in get_cells_overlapping: " << col.type
              << std::endl;
  }

  return ids;
}

void CollisionGrid::debug_draw_grid(SDL_Renderer *renderer) {

  for (auto cell_iter = registered_cells.begin();
       cell_iter != registered_cells.end(); cell_iter++) {
    collision_cell_id cell_id = (collision_cell_id)*cell_iter;
    // std::cout << cell_id << std::endl;

    int row = cell_id >> 4;
    int col = cell_id - (row << 4);

    // std::cout << "Row " << row << ", Col " << col << std::endl;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_FRect r = {(float)col * COLLISION_CELL_SIZE,
                   (float)row * COLLISION_CELL_SIZE, COLLISION_CELL_SIZE,
                   COLLISION_CELL_SIZE};
    SDL_RenderRect(renderer, &r);
  }
}

void CollisionGrid::debug_cout_cell(collision_cell_id id) {
  debug_cout_cell_id(id);
  std::cout << ": ";
  for (auto e = cells[id].begin(); e != cells[id].end(); e++) {
    Entity ent = (Entity)*e;
    std::cout << ent << ", ";
  }
  std::cout << std::endl;
}

// void CollisionGrid::debug_cout_ent(collision_cell_id id) {
//   debug_cout_cell_id(id);
//   for (auto ent=cells[
// }

void CollisionGrid::debug_display() {
  for (auto ci = registered_cells.begin(); ci != registered_cells.end(); ci++) {
    collision_cell_id id = (collision_cell_id)*ci;
    debug_cout_cell(id);
  }
}
