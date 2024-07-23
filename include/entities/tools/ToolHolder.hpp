#pragma once

#include <entities/Entity.hpp>

// Invisible tiny entity that just moves to the mouse, for the purpose of tool holding

class ToolHolder : public Entity {
public:
  ToolHolder() = default;
  ToolHolder(float x, float y);
  void drop_tool();
  void activate_tool() override;
  //void draw(sf::RenderWindow *window) override;
};
