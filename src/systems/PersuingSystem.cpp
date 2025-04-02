#include <engine/Components.hpp>
#include <systems/PersuingSystem.h>

void PersuingSystem::update(float dt) {
  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {
    Entity ent = (Entity)*e;
    Persuing p = *component_manager->get_component_data<Persuing>(ent);
    Position *pos = component_manager->get_component_data<Position>(ent);

    sf::Vector2f vecPos = sf::Vector2f(pos->x, pos->y);
    sf::Vector2f desiredPos = sf::Vector2f(p.desiredX, p.desiredY);
    sf::Vector2f diff = vecPos - desiredPos;
    sf::Vector2f dir = diff.normalized();

    sf::Vector2f newPos = vecPos + dir;

    pos->x -= dir.x * 0.1;
    pos->y -= dir.y * 0.1;

    std::cout << newPos.x << ", " << newPos.y << std::endl;

    std::cout << "Entity " << ent << " is persuing " << p.desiredX << ", "
              << p.desiredY << std::endl;
  }
}
