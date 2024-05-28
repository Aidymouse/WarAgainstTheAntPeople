#include <entities/Entity.hpp>
#include <entities/tools/Tool.hpp>
#include <memory>
#include <types/CollisionShapes.hpp>
#include <SFML/Audio.hpp>

#pragma once
class Mallet : public Tool {
public:
  Mallet(float x, float y);
  sf::Sound sound;
  void draw(sf::RenderWindow *window) override;
  void handle_event(sf::Event *event) override;
  std::string type() override;
  void pick_up() override;
  void set_down() override;
  void update(float dt) override;
};
