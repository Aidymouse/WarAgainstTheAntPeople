#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

#include <systems/ToolMouse.h>
#include <SFML/Window/Event.hpp>
#include <engine/Components.hpp>
#include <engine/Collisions.h>

void ToolMouse::handle_click(const sf::Event::MouseButtonPressed* evt) {

	if (held_tool != -1) {

		if (evt->button == sf::Mouse::Button::Left) {
			// Activate Tool	
		} else if (evt->button == sf::Mouse::Button::Right) {
			// Put tool down
		}

	} else {

		if (evt->button == sf::Mouse::Button::Left) {

			for (auto e=registered_entities.begin(); e != registered_entities.end(); e++) {
				Entity ent = (Entity) *e;
				Collider col = component_manager->get_component_data<Collider>(ent);

				if (Collisions::circle_circle(
					col.shape.circle, 
					{(float)evt->position.x, (float)evt->position.y, 1}
				)) {
					std::cout << "Clicked on " << ent << std::endl;
				}

			}

		}
	}


}

void ToolMouse::handle_mousemove(const sf::Event::MouseMoved* evt) {
	mouseX = evt->position.x;
	mouseY = evt->position.y;

	if (held_tool != -1) {
		// Update tool pos
	}
}

void ToolMouse::draw(sf::RenderTarget* target) {
	
	sf::CircleShape circle;
	circle.setOutlineColor(sf::Color::Red);

	for (auto e=registered_entities.begin(); e != registered_entities.end(); e++) {
		Entity ent = (Entity) *e;
		Collider col = component_manager->get_component_data<Collider>(ent);

		circle.setPosition({col.shape.circle.x, col.shape.circle.y});
		circle.setRadius(col.shape.circle.radius);
		target->draw(circle);
	}

	circle.setPosition({(float)mouseX, (float)mouseY});
	circle.setRadius(1);
	target->draw(circle);


};

