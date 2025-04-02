#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

class DrawSystem : public System {
public:
  void update(float dt, ECS *ecs);
  void draw(sf::RenderTarget *target);
};
