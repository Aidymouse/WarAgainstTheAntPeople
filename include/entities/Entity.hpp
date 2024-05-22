#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

#include <types/Animation.hpp>
#include <types/CollisionShapes.hpp>
#include <types/Collisions.hpp>

#pragma once

struct debug_info {
  float show_collider_timer;
};

class Entity {
public:

  Entity() = default;
  Entity(float x, float y);
  sf::Vector3<float> pos;

  Collider collider;

  debug_info debug;

  bool decoration = false;
  bool marked_for_deletion = false;
  bool should_update_collision = false;

  virtual void update(float dt){};
  virtual void draw(sf::RenderWindow *window);
  virtual void draw_collider(sf::RenderWindow *window, sf::Color outline = sf::Color(255, 0 ,0));
  virtual void handle_collision(Collision collision){};

  std::vector<std::string> inhabited_cell_ids;
  virtual void update_collision_cells(std::vector<std::string> ids);

  sf::Texture tex;
  sf::Sprite sprite;
  animation *cur_anim = NULL;
  float animation_timer = 0;
  virtual void update_animation(float dt);
  virtual void init_animation(animation *anim);
  virtual void update_collider();
  virtual std::string type();
};
