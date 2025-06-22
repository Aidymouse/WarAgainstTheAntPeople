#include "SDL3/SDL_render.h"
#include "components/Components.hpp"
#include "engine/Collisions.h"
#include <ProjectConfig.h>
#include <ecs/ECS.hpp>
#include <engine/CollisionGrid.h>
#include <iostream>
#include <util/Vec2.hpp>

ColCellId get_cell_id(int row, int col) { return (row << 4) + col; }
Vec2 get_cell_row_col(ColCellId id) {
  int row = id >> 4;
  int col = id - (row << 4);
  return Vec2(row, col);
}

void debug_cout_cell_id(ColCellId id) {
  Vec2 row_col = get_cell_row_col(id);
  std::cout << "Cell " << id << " (" << row_col.x << ", " << row_col.y << ") ";
}

CollisionGrid::CollisionGrid() {
  int cols = WINDOW_WIDTH / COLLISION_CELL_SIZE + 1;
  int rows = WINDOW_HEIGHT / COLLISION_CELL_SIZE + 1;

  for (int col = 0; col < cols; col++) {
    for (int row = 0; row < rows; row++) {
      ColCellId id = (row << 4) + col;

      registered_cells.insert(id);
    }
  }
}

// FOR NOW! Remove all cells then reapply all
void CollisionGrid::update_entity(Entity ent, Position pos, Collider col) {

  // collision_cell_id prev = -1;

  collision_cell inhabited_cell = inhabited_cells[ent];

  // if (inhabited_cells[ent].size() > 0) {
  //   prev = (int)*inhabited_cells[ent].begin();
  // }

  for (auto cell_iter = inhabited_cell.begin();
       cell_iter != inhabited_cell.end(); cell_iter++) {
    ColCellId cell_id = (ColCellId)*cell_iter;
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

  ColCellId new_id = get_cell_id(init_row, init_col);
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

void CollisionGrid::remove_entity(Entity ent) {
  collision_cell inhabited = inhabited_cells[ent];

  for (auto cell_iter = inhabited.begin(); cell_iter != inhabited.end();
       cell_iter++) {
    ColCellId cell_id = (ColCellId)*cell_iter;
    cells[cell_id].erase(ent);
  }

  inhabited_cells[ent].clear();
  std::set<ColCellId> s = inhabited_cells[ent];
}

std::set<ColCellId> CollisionGrid::get_cells_for_entity(Entity ent) {
  return inhabited_cells[ent];
}

std::set<ColCellId> CollisionGrid::get_overlapping_cells(Collider col) {

  std::set<ColCellId> ids;
  SDL_Rect effective_dims = {0, 0, 0, 0};

  // Convert all shapes to a upper right hand corner bounding box
  if (col.type == CollisionShapeType::CIRCLE) {
    effective_dims.x = col.shape.circle.x - col.shape.circle.radius;
    effective_dims.y = col.shape.circle.y - col.shape.circle.radius;
    effective_dims.w = col.shape.circle.radius * 2;
    effective_dims.h = col.shape.circle.radius * 2;
  }

  int init_col = effective_dims.x / COLLISION_CELL_SIZE;
  int init_row = effective_dims.y / COLLISION_CELL_SIZE;
  // std::cout << "Init: " << init_row << ", " << init_col << std::endl;

  int additional_cells_right = effective_dims.w / COLLISION_CELL_SIZE + 1;
  int additional_cells_down = effective_dims.h / COLLISION_CELL_SIZE + 1;

  // std::cout << "Additional cells ->: " << additional_cells_right
  //           << " v: " << additional_cells_down << std::endl;

  for (int col = init_col; col <= init_col + additional_cells_right; col++) {
    for (int row = init_row; row <= init_row + additional_cells_down; row++) {
      // std::cout << "Testing " << row << ", " << col << std::endl;
      ColCellId id = get_cell_id(row, col);
      ids.insert(id);
    }
  }

  return ids;
}

/* Is this a chance for move semantices (new toy) ? */
std::set<Entity> CollisionGrid::test_entity_for_collisions(Entity ent,
                                                           ECS *ecs) {
  std::set<Entity> collided_entities;

  Collider *ent_collider = ecs->get_component_for_entity<Collider>(ent);

  std::set<ColCellId> ent_cell_ids = get_cells_for_entity(ent);

  for (auto id_iter = ent_cell_ids.begin(); id_iter != ent_cell_ids.end();
       id_iter++) {
    ColCellId cell_id = (ColCellId)*id_iter;

    std::set<Entity> cell_entity_ids = cells[cell_id];

    for (auto entity_iter = cell_entity_ids.begin();
         entity_iter != cell_entity_ids.end(); entity_iter++) {
      Entity col_ent = (Entity)*entity_iter;

      /** This could theoretically fail but I don't think it will since you need
       * to give a collider for the entity to be put into the grid... Wait... it
       * doesn't need to be their own collider... WARN: this could be a bug
       * */
      Collider *c = ecs->get_component_for_entity<Collider>(col_ent);

      if (Collisions::collision(*c, *ent_collider)) {
        // Need to dedupe?
        collided_entities.insert(col_ent);
      };
    }
  }

  return collided_entities;
}

std::set<Entity> CollisionGrid::get_collisions(Collider col, ECS *ecs) {
  std::set<Entity> collided_entities;

  std::set<ColCellId> relevant_cell_ids = get_overlapping_cells(col);
  // std::set < Cel

  for (auto id_iter = relevant_cell_ids.begin();
       id_iter != relevant_cell_ids.end(); id_iter++) {
    ColCellId cell_id = (ColCellId)*id_iter;

    std::set<Entity> cell_entity_ids = cells[cell_id];

    for (auto entity_iter = cell_entity_ids.begin();
         entity_iter != cell_entity_ids.end(); entity_iter++) {
      Entity col_ent = (Entity)*entity_iter;

      /** This could theoretically fail but I don't think it will since you
      need
       * to give a collider for the entity to be put into the grid... Wait...
       it
       * doesn't need to be their own collider... WARN: this could be a bug
       * */
      Collider *c = ecs->get_component_for_entity<Collider>(col_ent);

      if (Collisions::collision(*c, col)) {
        // Need to dedupe?
        collided_entities.insert(col_ent);
      };
    }
  }

  return collided_entities;
}

void CollisionGrid::debug_draw_grid(SDL_Renderer *renderer) {

  for (auto cell_iter = registered_cells.begin();
       cell_iter != registered_cells.end(); cell_iter++) {
    ColCellId cell_id = (ColCellId)*cell_iter;
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

void CollisionGrid::debug_cout_cell(ColCellId id) {
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
    ColCellId id = (ColCellId)*ci;
    debug_cout_cell(id);
  }
}

void CollisionGrid::debug_cout_entity_state(Entity id) {
  std::cout << "[" << id << "] ColGrid - ";
  // inhabited_cells =
  if (inhabited_cells.find(id) == inhabited_cells.end()) {
    std::cout << "Inhabits no cells";
  } else {
    std::set<ColCellId> inhabited_cell_ids = inhabited_cells[id];
    std::cout << "Inhabits ";
    for (auto cid = inhabited_cell_ids.begin(); cid != inhabited_cell_ids.end();
         cid++) {
      ColCellId cell_id = (ColCellId)*cid;
      debug_cout_cell_id(cell_id);
    }
  }
  std::cout << std::endl;
};
