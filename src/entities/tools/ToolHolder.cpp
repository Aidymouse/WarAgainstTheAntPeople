#include "SFML/Graphics/RenderWindow.hpp"
#include <entities/Entity.hpp>
#include <entities/tools/ToolHolder.hpp>
#include <entities/tools/Tool.hpp>
#include <iostream>

ToolHolder::ToolHolder(float x, float y) : Entity::Entity(x, y) {
}

void ToolHolder::activate_tool() {
  if (held_tool) {
    held_tool->activate();
  } else {
    std::cout << "No tool!!!";
  }
}

void ToolHolder::drop_tool() {
  held_tool->set_down();
  held_tool.reset();
}

// void ToolHolder::draw(sf::RenderWindow *window) {
// }
