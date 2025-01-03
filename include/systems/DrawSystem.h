#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <ecs/System.hpp>

class DrawSystem : public System {
public:
	void update(float dt);
	void draw(sf::RenderTarget* target);
};
