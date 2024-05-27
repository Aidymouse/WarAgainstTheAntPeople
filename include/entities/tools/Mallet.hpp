#include <types/CollisionShapes.hpp>
#include <entities/tools/Tool.hpp>

#include <SFML/Audio.hpp>

#pragma once
class Mallet : public Tool {
public:
  Mallet(std::string tex_filename, float origin_x, float origin_y);
  sf::Sound sound;
  void draw(sf::RenderWindow *window) override;
  void handle_event(sf::Event *event) override;
  Collider collider;
};
