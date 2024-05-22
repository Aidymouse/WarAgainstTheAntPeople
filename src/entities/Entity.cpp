#include "../include/Entities/Entity.h"
#include "../include/Types/Animation.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

class Entity;

Entity::Entity(float x, float y) {
  pos.x = x;
  pos.y = y;
}

void Entity::draw(sf::RenderWindow *window) {
  window->draw(sprite);
}

void Entity::draw_collider(sf::RenderWindow *window, sf::Color color) {
  if (collider.type == CollisionShapeType::RECT) {
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(collider.x, collider.y));
    rect.setSize(sf::Vector2f(collider.collisionShape.rect.width, collider.collisionShape.rect.height));
    rect.setFillColor(sf::Color(0, 0, 0, 0));
    rect.setOutlineThickness(2);
    rect.setOutlineColor(color);
    window->draw(rect);

  } else if (collider.type == CollisionShapeType::CIRCLE) {
    sf::CircleShape circle;
    float radius = collider.collisionShape.circle.radius;
    circle.setPosition(sf::Vector2f(collider.x, collider.y));
    //circle.setPosition(sf::Vector2f(0, 0));
    circle.setRadius(collider.collisionShape.circle.radius);
    circle.setFillColor(sf::Color(0, 0, 0, 0));
    circle.setOutlineThickness(2);
    circle.setOutlineColor(color);
    window->draw(circle);

  } else {
    std::cout << "No collider type set! Can't draw!";
  }
}

std::string Entity::type() { return "Entity"; }

void Entity::init_animation(animation *anim) {
  cur_anim = anim;
  sprite.setTextureRect(anim->texture_rectangle);
  sprite.setPosition(pos.x - cur_anim->origin_x, pos.y - cur_anim->origin_y);
  animation_timer = anim->duration;
}

void Entity::update_animation(float dt) {
  if (cur_anim->next_anim == NULL) {
    return;
  }
  // To account for frame times longer than animation, or times where an
  // animation changes in the middle of the frame, we use this little loop to
  // make sure everything lines up
  float delta = dt;
  while (delta > 0) {
    animation_timer -= delta;
    delta = -animation_timer;
    if (animation_timer <= 0) {
      cur_anim = cur_anim->next_anim;
      animation_timer = cur_anim->duration;
      sprite.setTextureRect(cur_anim->texture_rectangle);
      sprite.setPosition(pos.x - cur_anim->origin_x,
                         pos.y - cur_anim->origin_y);
      if (cur_anim->next_anim == NULL)
        return;
    }
  }
}

void Entity::update_collider() {
  collider.x = pos.x;
  collider.y = pos.y;
}

void Entity::update_collision_cells(std::vector<std::string> inhabited_ids) {
  // TODO
  // Does this just work??
  inhabited_cell_ids = inhabited_ids;
}

