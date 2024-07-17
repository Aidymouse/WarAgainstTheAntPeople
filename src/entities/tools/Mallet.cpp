#pragma once
#include <state/AudioManager.hpp>
#include <state/GraphicsManager.hpp>
#include <state/CollisionManager.hpp>
#include <state/Gamestate.hpp>
#include <helper/Helper.hpp>
#include <helper/AnimationGenerator.hpp>
#include <types/Collisions.hpp>
#include <entities/tools/Mallet.hpp>
#include <entities/tools/Tool.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <types/ToolStates.hpp>

std::vector<sf::IntRect> mallet_graphic_rects = AnimationGenerator::generate_texture_rects(128, 128, 32, 32);

struct {
  const sf::IntRect up = mallet_graphic_rects.at(0);
  const sf::IntRect smash = mallet_graphic_rects.at(1);
  const sf::IntRect lying = mallet_graphic_rects.at(2);
} mallet_rects;


const float MALLET_RANGE = 20.0;

Mallet::Mallet(float x, float y) : Tool::Tool(x, y) {

  sprite.setTexture( *GraphicsManager::textures["mallet"]);
  sprite.setPosition( sf::Vector2f(x+sprite_offset.x, y+sprite_offset.y) );
  sprite.setTextureRect(mallet_rects.lying);

  sprite_offset.x = 16;
  sprite_offset.y = 16;
  sprite.setOrigin(sprite_offset.x, sprite_offset.y);

  collider.type = CollisionShapeType::CIRCLE;
  collider.collisionShape.circle.radius = 16;
  collider.x = x;
  collider.y = y;

}

void Mallet::update(float dt) {
  
  if (equipped) {
    pos.x = Gamestate::mouse_pos.x;
    pos.y = Gamestate::mouse_pos.y;
  }

  switch (state) {
    case Mallet_States::LYING: { break; }

    case Mallet_States::SMASHING: {
      timers.smashing -= dt;
      if (timers.smashing <= 0) {
        sprite.setTextureRect(mallet_rects.smash);

        // Collisions
        std::vector<grid_cell *> mallet_cells = Gamestate::main_grid.get_cells_within(MALLET_RANGE, pos.x, pos.y);

        for (auto &cell : mallet_cells) {
          for (auto &ent : *cell) {

            // float dist = Helper::dist_tween_points(
            // evt.mouseButton.x, evt.mouseButton.y, ent->pos.x, ent->pos.y);
            collider.x = pos.x;
            collider.y = pos.y;

            if (CollisionManager::does_collide(&collider, &(ent->collider))) {
              Collision col;
              col.type = Collisions::MALLET;

              ent->handle_collision(col);
            }
          }
        }

        timers.rising = durations.rising;
        state = Mallet_States::RISING;
      }
    }

    case Mallet_States::RISING: {
      timers.rising -= dt;
      if (timers.rising <= 0) {
        sprite.setTextureRect(mallet_rects.up);
        state = Mallet_States::HELD;
      }
      break;
    }
  }

  //update_animation(dt);
  generic_upkeep();
}

void Mallet::activate() {
  if (state != Mallet_States::HELD) return;

  timers.smashing = durations.smashing;
  state = Mallet_States::SMASHING;
}

void Mallet::handle_event(sf::Event *event) {}

void Mallet::draw(sf::RenderWindow *window) { window->draw(sprite); }

std::string Mallet::type() { return "Mallet"; }

void Mallet::pick_up() {
  equipped = true;
  sprite_offset.y = 32;
  sprite.setTextureRect(mallet_rects.up);
  state = Mallet_States::HELD;
}

void Mallet::set_down() {
  equipped = false;
  sprite_offset.y = 16;
  sprite.setTextureRect(mallet_rects.lying);
  state = Mallet_States::LYING;
  // TODO: Update position in the collision grid
}

