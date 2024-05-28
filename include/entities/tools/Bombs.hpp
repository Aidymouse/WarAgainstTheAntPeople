#include <entities/tools/Tool.hpp>
#include <SFML/Graphics.hpp>

#pragma once
class Bombs : public Tool {
public:
  Bombs(float x, float y);
  void handle_event(sf::Event *event) override;
  sf::Texture bomb_tex;
};
