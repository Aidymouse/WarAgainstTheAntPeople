#include "../include/Tools/Mallet.h"
#include "../include/Lib/AudioManager.h"
#include "../include/Lib/Gamestate.h"
#include "../include/Lib/Helper.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

struct {
  const sf::IntRect up = sf::IntRect(0, 0, 32, 32);
  const sf::IntRect smash = sf::IntRect(32, 0, 32, 32);
} mallet_rects;

const float MALLET_RANGE = 20.0;

Mallet::Mallet(std::string tex_filename, float origin_x, float origin_y)
    : Tool::Tool(tex_filename, origin_x, origin_y) {
  sprite.setTextureRect(mallet_rects.up);
}

void Mallet::handle_event(sf::Event *event) {

  sf::Event evt = *event;

  if (evt.type == sf::Event::MouseButtonPressed) {

    if (evt.mouseButton.button == sf::Mouse::Left) {

      int splat_number = Helper::random(1, 3);
      // AudioManager::play_sound("splat" + std::to_string(splat_number));
      // AudioManager::play_sound("vine boom");

      // Graphic
      sprite.setTextureRect(mallet_rects.smash);

      // Collisions
      std::vector<grid_cell *> mallet_cells =
          Gamestate::main_grid.get_cells_within(MALLET_RANGE, evt.mouseButton.x,
                                                evt.mouseButton.y);

      for (auto &cell : mallet_cells) {
        for (auto &ent : *cell) {

          float dist = Helper::dist_tween_points(
              evt.mouseButton.x, evt.mouseButton.y, ent->pos.x, ent->pos.y);

          if (dist <= MALLET_RANGE) {
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
