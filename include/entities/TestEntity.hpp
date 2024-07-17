#pragma once

#include <entities/Entity.hpp>
#include <SFML/Graphics.hpp>

class TestEntity : public Entity {
public:
  std::string type = "Test Entity";
  sf::Sprite sprite;
  sf::Texture *tex;
  animation *cur_anim;

  TestEntity(sf::Texture *t, float x, float y);
  void draw(sf::RenderWindow *window) override;
};
