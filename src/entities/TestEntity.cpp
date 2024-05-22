#include "../include/Entities/TestEntity.h"
#include "../include/Entities/Entity.h"
#include "SFML/Graphics/Color.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class TestEntity;

TestEntity::TestEntity(sf::Texture *t, float x, float y) : Entity::Entity(x, y) {
  //tex = t;
  //sprite.setTexture(*tex);
  //sprite.setPosition(pos.x, pos.y);

  //collider.collisionShape.rect.width = 64;
  //collider.collisionShape.rect.height = 64;
  collider.collisionShape.circle.radius = 20;
  collider.type = CollisionShapeType::CIRCLE;
  collider.x = x-20;
  collider.y = y-20;
}


void TestEntity::draw(sf::RenderWindow *window) {
  draw_collider(window, sf::Color(0, 255, 0));
}

