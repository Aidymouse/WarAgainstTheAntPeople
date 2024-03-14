#include "../Entity.h"
#include <SFML/Graphics.hpp>

#pragma once
class Bloodstain : public Entity {
public:
  Bloodstain(float x, float y);
  sf::CircleShape ellipse;
  void draw(sf::RenderWindow *window) override;
  void update(float dt) override;
};
