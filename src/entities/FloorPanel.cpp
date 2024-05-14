#include "../include/Entities/FloorPanel.h"
#include "../include/Lib/GraphicsManager.h"
#include "../include/Types/Collisions.h"
#include <iostream>

FloorPanel::FloorPanel(float x, float y) : Entity::Entity(x, y) {
  pos.z = -1;
  tex = GraphicsManager::textures["floorpanel"];
  sprite.setTexture(*tex);
  sprite.setPosition(pos.x, pos.y);

  collider.collisionShape.rect.width = 64;
  collider.collisionShape.rect.height = 64;
  collider.type = CollisionShapeType::RECT;
  collider.x = x;
  collider.y = y;
}

void FloorPanel::update(float dt) {
  // idk
  if (shake_timer > 0) {
    int shake_force = ceil(max_shake_force * shake_timer / max_shake_timer);

    offset.x = rand() % shake_force * 2 - shake_force;
    offset.y = rand() % shake_force * 2 - shake_force;
    // std::cout << dt;
    shake_timer -= dt;

    sprite.setPosition(pos.x + offset.x, pos.y + offset.y);

    if (shake_timer <= 0) {
      sprite.setPosition(pos.x, pos.y);
    }
  }
}

void FloorPanel::draw(sf::RenderWindow *window) { window->draw(sprite); }

void FloorPanel::say_type() { std::cout << "FloorPanel" << std::endl; }

void FloorPanel::handle_collision(Collision collision) {
  if (collision.type == Collisions::MALLET) {
    for (int i = 0; i < inhabited_cell_ids.size(); i++) {
      std::cout << inhabited_cell_ids.at(i);
    }
    shake_timer = max_shake_timer;
  }
}
