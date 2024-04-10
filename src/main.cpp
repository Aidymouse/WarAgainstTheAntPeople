#include "include/Entities/Entity.h"
#include "include/Entities/FloorPanel.h"
#include "include/Entities/Guy.h"
#include "include/Lib/AudioManager.h"
#include "include/Lib/Gamestate.h"
#include "include/Lib/GraphicsManager.h"
#include "include/Tools/Bombs.h"
#include "include/Tools/Mallet.h"
#include "include/lib/ParticleSystem.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <memory>
#include <stdlib.h>
#include <string>
#include <time.h>

const int NUM_GUYS = 1000;

const int WINDOW_WIDTH = 800u;
const int WINDOW_HEIGHT = 600u;

// I have no idea why this doesn't work

bool compare_entities(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2) {
  if (e1->pos.z != e2->pos.z) {
    return e1->pos.z < e2->pos.z; // Compare z positions first
  } else {
    return e1->pos.y <
           e2->pos.y; // If z positions are equal, compare y positions
  }
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
  sf::Texture tex;
  tex.loadFromFile(graphics_path + "guy sheet.png");

  GraphicsManager::load_texture("floorpanel", graphics_path + "floorpanel.png");

  // Set up delta time clock
  sf::Clock delta_clock;
  float delta_time;

  // LOAD
  sf::Time elapsed;
  Mallet mallet(graphics_path + "mallet.png", 32, 32);
  Bombs bombs(graphics_path + "bombs.png", 16, 16);
  const int NUM_TOOLS = 2;
  Tool *tools[NUM_TOOLS] = {&mallet, &bombs};
  int current_tool_index = 0;
  Tool *current_tool = tools[current_tool_index];

  // Make Guys
  for (int i = 0; i < NUM_GUYS; i++) {
    Gamestate::insert_entity(std::make_shared<Guy>(&tex, rand() % WINDOW_WIDTH,
                                                   rand() % WINDOW_HEIGHT));
  }

  // Make Floor Panels
  int floor_panel_rows = WINDOW_HEIGHT / 64 + 1;
  int floor_panel_columns = WINDOW_WIDTH / 64 + 1;

  for (int row = 0; row < floor_panel_rows; row++) {
    for (int col = 0; col < floor_panel_columns; col++) {
      Gamestate::insert_entity(
          std::make_shared<FloorPanel>(col * 64, row * 64));
    }
  }

  // Game Loop
  while (window.isOpen()) {
    // EVENTS
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed) {
      }
      if (event.type == sf::Event::MouseWheelScrolled) {
        current_tool_index +=
            event.mouseWheelScroll.delta / abs(event.mouseWheelScroll.delta);
        if (current_tool_index > NUM_TOOLS - 1)
          current_tool_index = 0;
        if (current_tool_index < 0)
          current_tool_index = NUM_TOOLS - 1;
        current_tool = tools[current_tool_index];
      }
      current_tool->handle_event(&event);
    }

    // UPDATE
    elapsed = delta_clock.restart();
    delta_time = elapsed.asSeconds();

    AudioManager::update(delta_time);

    for (auto &ent : Gamestate::entities) {
      ent->update(delta_time);
    }

    Gamestate::remove_marked_entities();

    current_tool->update(delta_time, &window);

    // DRAW

    std::sort(Gamestate::entities.begin(), Gamestate::entities.end(),
              compare_entities);

    window.clear(sf::Color(229, 229, 229));
    for (auto &ent : Gamestate::entities) {
      ent->draw(&window);
    }

    current_tool->draw(&window);

    window.display();
  }
}
