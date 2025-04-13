#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include <engine/CollisionGrid.h>

#include <iostream>

CollisionGrid::CollisionGrid() {
  int cells_across = WINDOW_WIDTH / COLLISION_CELL_SIZE;
  int cells_down = WINDOW_HEIGHT / COLLISION_CELL_SIZE;
  // int cells_across = 10;
  // int cells_down = 10;

  for (int row = 0; row < cells_across; row++) {
    for (int col = 0; col < cells_down; col++) {
      collision_cell_id id = (row << 4) + col;
      // std::cout << "Cell Id " << id << " Row " << row << ", Col " << col
      //           << std::endl;

      registered_cells.insert(id);
      collision_cell cell;
      cells[id] = cell;
    }
  }
}

void CollisionGrid::update_entity(Entity ent, Position pos) {
  if (inhabited_cells[ent].size() == 0) {
    std::cout << "New to grid: " << ent << std::endl;
    inhabited_cells[ent].insert(1);
  }
};

void CollisionGrid::debug_draw_grid(sf::RenderTarget *target) {

  sf::RectangleShape rect;
  rect.setOutlineColor(sf::Color::Red);
  rect.setOutlineThickness(1);
  rect.setFillColor(sf::Color::Transparent);
  rect.setSize({(float)COLLISION_CELL_SIZE, (float)COLLISION_CELL_SIZE});

  for (auto cell_id = registered_cells.begin();
       cell_id != registered_cells.end(); cell_id++) {
    collision_cell_id id = (collision_cell_id)*cell_id;

    int row = id >> 4;
    int col = id - (row << 4);
    // std::cout << "r" << row << ", c" << col << std::endl;
    //
    // std::cout << "M" << id << std::endl;

    // sf::IntRect rect(,
    //                  {COLLISION_CELL_SIZE, COLLISION_CELL_SIZE});
    rect.setPosition(
        {(float)row * COLLISION_CELL_SIZE, (float)col * COLLISION_CELL_SIZE});

    target->draw(rect);
    // std::cout << "Collision Cell: " << id << "(" << row << ", " << col << ")"
    // << std::endl;
  }
  // sf::IntRect rect({0, 0}, {})
  // target->draw();
};
