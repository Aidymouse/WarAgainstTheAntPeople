#pragma once

#include <entities/Entity.hpp>

// Invisible tiny entity that just moves to the mouse, for the purpose of tool holding
class Tool;

class ToolHolder : public Entity {
public:
  ToolHolder(float x, float y);
  void activate_tool() override;
  std::shared_ptr<Tool> holding;
};
