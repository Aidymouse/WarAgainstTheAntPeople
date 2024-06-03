#include <entities/Entity.hpp>
#include <entities/tools/Tool.hpp>
#include <types/CollisionShapes.hpp>
#include <SFML/Audio.hpp>
#include <types/ToolStates.hpp>

#pragma once
class Mallet : public Tool {
public:
  Mallet_States state = Mallet_States::LYING;
  sf::Sound sound;
  struct { 
    float smashing = 0.0f;
    float rising = 0.2f;
  } durations;
  struct {
    float smashing = 0;
    float rising = 0;
  } timers;

public:
  Mallet(float x, float y);
  void draw(sf::RenderWindow *window) override;
  void handle_event(sf::Event *event) override;
  std::string type() override;
  void pick_up() override;
  void set_down() override;
  void activate() override;
  void update(float dt) override;
};
