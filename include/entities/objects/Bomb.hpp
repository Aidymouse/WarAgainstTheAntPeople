#include "Entity.h"

const int BOMB_RADIUS = 10;
const int EXPLOSION_RADIUS = 50;
const float MAX_FUSE_TIMER = 3;
const float MAX_LIFETIME = 4;

#pragma once
class Bomb : public Entity {
public:
  std::string type = "Bomb";
  sf::CircleShape ellipse;
  sf::Texture *tex;
  float timer = MAX_FUSE_TIMER;
  float lifetime = MAX_LIFETIME;
  Bomb(sf::Texture *tex, float x, float y);
  void update(float dt) override;
  void draw(sf::RenderWindow *window) override;
  bool exploded = false;
};
