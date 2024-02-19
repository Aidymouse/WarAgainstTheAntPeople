#include "Entities/Decorations/Bloodstain.h"

Bloodstain::Bloodstain(float x, float y) : Entity::Entity(x, y) {
	decoration = true;

	ellipse = sf::CircleShape(5.0f);
	ellipse.setScale(1, 0.5);
	ellipse.setFillColor(sf::Color(255, 0, 0));
	ellipse.setPosition(pos.x, pos.y);
}

void Bloodstain::draw(sf::RenderWindow* window) {
	window->draw(ellipse);
};