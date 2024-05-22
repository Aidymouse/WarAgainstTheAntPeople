#include "../Entities/Entity.h"
#include <SFML/Graphics.hpp>

#pragma once

class TestEntity : public Entity {
public:
  std::string type = "Test Entity";
  sf::Sprite sprite;
  sf::Texture *tex;
  animation *cur_anim;

  TestEntity(sf::Texture *t, float x, float y);
  void draw(sf::RenderWindow *window) override;
};
