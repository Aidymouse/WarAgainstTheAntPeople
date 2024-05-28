#include <entities/tools/Tool.hpp>

#include <SFML/Graphics.hpp>

#pragma once
class Fire : public Tool {
public:
  Fire(float x, float y);
  void draw(sf::RenderWindow *window) override;
  void handle_event(sf::Event *event) override;
};
