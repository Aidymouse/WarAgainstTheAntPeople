#include <state/AudioManager.hpp>
#include <state/GraphicsManager.hpp>
#include <state/CollisionManager.hpp>
#include <state/Gamestate.hpp>
#include <helper/Helper.hpp>
#include <helper/AnimationGenerator.hpp>
#include <types/Collisions.hpp>
#include <entities/tools/Mallet.hpp>
#include <entities/Entity.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

std::vector<sf::IntRect> mallet_graphic_rects = AnimationGenerator::generate_texture_rects(128, 128, 32, 32);

struct {
  const sf::IntRect up = mallet_graphic_rects.at(0);
  const sf::IntRect smash = mallet_graphic_rects.at(1);
  const sf::IntRect lying = mallet_graphic_rects.at(2);
} mallet_rects;

const float MALLET_RANGE = 20.0;

Mallet::Mallet(float x, float y) : Entity::Entity(x, y) {

  sprite.setTexture( *GraphicsManager::textures["mallet"]);
  sprite.setPosition( sf::Vector2f(x+sprite_offset.x, y+sprite_offset.y) );
  sprite.setTextureRect(mallet_rects.lying);

  sprite.setOrigin(16, 16);

  collider.type = CollisionShapeType::CIRCLE;
  collider.collisionShape.circle.radius = 16;
  collider.x = x;
  collider.y = y;

}

void Mallet::handle_event(sf::Event *event) {

  sf::Event evt = *event;

  if (evt.type == sf::Event::MouseButtonPressed) {

    if (evt.mouseButton.button == sf::Mouse::Left) {

      // int splat_number = Helper::random(1, 3);
      // AudioManager::play_sound("splat" + std::to_string(splat_number));
      // AudioManager::play_sound("vine boom");

      // Graphic
      sprite.setTextureRect(mallet_rects.smash);

      // Collisions
      std::vector<grid_cell *> mallet_cells = Gamestate::main_grid.get_cells_within(MALLET_RANGE, evt.mouseButton.x, evt.mouseButton.y);

      for (auto &cell : mallet_cells) {
        for (auto &ent : *cell) {

          // float dist = Helper::dist_tween_points(
          // evt.mouseButton.x, evt.mouseButton.y, ent->pos.x, ent->pos.y);

          collider.x = evt.mouseButton.x;
          collider.y = evt.mouseButton.y; 

          if (CollisionManager::does_collide(&collider, &(ent->collider))) {
            Collision col;
            col.type = Collisions::MALLET;

            ent->handle_collision(col);
          }
        }
      }
    }
  }

  if (evt.type == sf::Event::MouseButtonReleased) {

    if (evt.mouseButton.button == sf::Mouse::Left) {
      sprite.setTextureRect(mallet_rects.up);
    }
  }
}

void Mallet::draw(sf::RenderWindow *window) { window->draw(sprite); }

std::string Mallet::type() {
  return "Mallet";
}
