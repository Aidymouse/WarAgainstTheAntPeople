#include <entities/tools/Bombs.hpp>
#include <entities/objects/Bomb.hpp>
#include <state/Gamestate.hpp>
#include <entities/tools/Tool.hpp>

Bombs::Bombs(std::string filename, float origin_x, float origin_y)
    : Tool::Tool(filename, origin_x, origin_y) {
  bomb_tex.loadFromFile((std::string)RESOURCE_PATH + "graphics/bomb sheet.png");
}

void Bombs::handle_event(sf::Event *event) {
  if (event->type == sf::Event::MouseButtonPressed) {
    if (event->mouseButton.button == sf::Mouse::Left) {
      Gamestate::insert_entity(std::make_shared<Bomb>(
          &bomb_tex, event->mouseButton.x, event->mouseButton.y));
    }
  }
}
