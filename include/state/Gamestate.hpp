#include <state/CollisionGrid.hpp>
#include <entities/tools/Tool.hpp>
#include <vector>

#pragma once
class Gamestate {
public:
  static const int WINDOW_WIDTH = 800u;
  static const int WINDOW_HEIGHT = 600u;

  static sf::Vector2i mouse_pos;

  static CollisionGrid main_grid;
  static std::vector<std::shared_ptr<Entity>> entities;
  static std::shared_ptr<Tool> equipped_tool;

  static std::shared_ptr<Entity> insert_entity(std::shared_ptr<Entity> ent);
  static void remove_marked_entities();
  static void remove_entity(std::shared_ptr<Entity> ent, int ent_index);
};

//const sf::RenderWindow Gamestate::window = sf::RenderWindow(sf::VideoMode(Gamestate::WINDOW_WIDTH, Gamestate::WINDOW_HEIGHT), "Evil Pikmin");
