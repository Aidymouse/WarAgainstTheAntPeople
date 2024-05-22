#include "Tool.h"
#include <SFML/Graphics.hpp>

#pragma once
class Bombs : public Tool {
public:
  Bombs(std::string filename, float origin_x, float origin_y);
  void handle_event(sf::Event *event) override;
  sf::Texture bomb_tex;
};
