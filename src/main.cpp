#include "SFML/Window/Event.hpp"
#include "state/CollisionManager.hpp"
#include "types/CollisionShapes.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <entities/Entity.hpp>
#include <entities/objects/FloorPanel.hpp>
#include <entities/TestEntity.hpp>
#include <entities/creatures/Guy.hpp>
#include <state/AudioManager.hpp>
#include <helper/Debug.hpp>
#include <state/Gamestate.hpp>
#include <state/GraphicsManager.hpp>
#include <entities/tools/Bombs.hpp>
#include <entities/tools/Mallet.hpp>
#include <state/ParticleSystem.hpp>

#include <algorithm>
#include <memory>
#include <stdlib.h>
#include <string>
#include <time.h>

const int NUM_GUYS = 000;

const int WINDOW_WIDTH = 800u;
const int WINDOW_HEIGHT = 600u;

bool compare_entities(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2) {
  if (e1->pos.z != e2->pos.z) return e1->pos.z < e2->pos.z; // Compare z positions first
  return e1->pos.y < e2->pos.y; // If z positions are equal, compare y positions
}

int main() {
  auto window = sf::RenderWindow{{WINDOW_WIDTH, WINDOW_HEIGHT}, "Evil Pikmin"};
  window.setFramerateLimit(144);

  // window.setMouseCursorVisible(false);

  // Seed Randomizer
  srand(time(NULL));

  std::string resource_path = RESOURCE_PATH;
  std::string graphics_path = resource_path + "graphics/";
  std::string audio_path = resource_path + "audio/";

  // Load Audio
  AudioManager::load_sound("splat1", audio_path + "splat 1.ogg");
  AudioManager::load_sound("splat2", audio_path + "splat 2.ogg");
  AudioManager::load_sound("splat3", audio_path + "splat 3.ogg");
  AudioManager::load_sound("mumble1", audio_path + "mumble 1.ogg");
  AudioManager::load_sound("mumble2", audio_path + "mumble 2.ogg");
  AudioManager::load_sound("mumble3", audio_path + "mumble 3.ogg");
  AudioManager::load_sound("vine boom", audio_path + "vine boom.ogg");

  // Load Textures
  GraphicsManager::load_texture("guy", graphics_path + "guy sheet.png");
  GraphicsManager::load_texture("floorpanel", graphics_path + "floorpanel.png");
  GraphicsManager::load_texture("mallet", graphics_path + "mallet.png");

  // Set up delta time clock
  sf::Clock delta_clock;
  float delta_time;

  // LOAD
  sf::Time elapsed;

  // Make Guys
  for (int i = 0; i < NUM_GUYS; i++) {
    Gamestate::insert_entity(std::make_shared<Guy>(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT));
  }

  // Make Floor Panels
  int floor_panel_rows = WINDOW_HEIGHT / 64 + 1;
  int floor_panel_columns = WINDOW_WIDTH / 64 + 1;

  for (int row = 0; row < floor_panel_rows; row++) {
    for (int col = 0; col < floor_panel_columns; col++) {
      //Gamestate::insert_entity(std::make_shared<FloorPanel>(col * 64, row * 64));
    }
  }

  // Add Tools
  enum tool_type { MALLET };
  std::shared_ptr<Entity> tools[1] = {
    std::make_shared<Mallet>(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT)
  };

  for (auto &tool : tools) {
    Gamestate::insert_entity(tool);
  }


  // Game Loop
  while (window.isOpen()) {
    // EVENTS
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        //Gamestate::insert_entity(std::make_shared<TestEntity>(&tex, event.mouseButton.x, event.mouseButton.y));
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
          Collider mouse_collider;
          mouse_collider.type = CollisionShapeType::CIRCLE;
          mouse_collider.collisionShape.circle.radius = 2;
          mouse_collider.x = event.mouseButton.x;
          mouse_collider.y = event.mouseButton.y;

          std::vector<grid_cell *> clicked_cells = Gamestate::main_grid.get_cells_within(1, mouse_collider.x, mouse_collider.y);

          for (auto &cell : clicked_cells) {
            for (auto &ent : *cell) {
              if (CollisionManager::does_collide(&mouse_collider, &(ent->collider))) {
                std::cout << ent->type();
              }
            }
          }
        }
      }

      if (event.type == sf::Event::MouseWheelScrolled) {
      }
    }

    // UPDATE
    elapsed = delta_clock.restart();
    delta_time = elapsed.asSeconds();

    AudioManager::update(delta_time);

    for (auto &ent : Gamestate::entities) {
      ent->update(delta_time);
    }

    Gamestate::remove_marked_entities();

    // DRAW

    std::sort(Gamestate::entities.begin(), Gamestate::entities.end(), compare_entities);

    window.clear(sf::Color(229, 229, 229));
    for (auto &ent : Gamestate::entities) {
      ent->draw(&window);
      if (Debug::draw_colliders) { ent->draw_collider(&window); }
    }

    if (Debug::DEBUG) Gamestate::main_grid.draw(&window);

    window.display();
  }
}
