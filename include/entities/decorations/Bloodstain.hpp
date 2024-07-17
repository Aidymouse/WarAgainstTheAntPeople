#pragma once

#include <entities/Entity.hpp>
#include <SFML/Graphics.hpp>

class Bloodstain : public Entity {
public:
  Bloodstain(float x, float y);
  sf::CircleShape ellipse;
  void draw(sf::RenderWindow *window) override;
  void update(float dt) override;
};
