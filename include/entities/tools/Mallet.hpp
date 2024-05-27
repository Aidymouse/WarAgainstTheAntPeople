#include <entities/Entity.hpp>
#include <types/CollisionShapes.hpp>
#include <SFML/Audio.hpp>

#pragma once
class Mallet : public Entity {
public:
  Mallet(float x, float y);
  sf::Sound sound;
  void draw(sf::RenderWindow *window) override;
  void handle_event(sf::Event *event);
  std::string type() override;
};
