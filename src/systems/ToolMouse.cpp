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
			Collider* tool_collider = component_manager->get_editable_component_data<Collider>(held_tool);
			tool_collider->shape.circle.x = evt->position.x;
			tool_collider->shape.circle.y = evt->position.y;
			held_tool = -1;

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
					//std::cout << "Clicked on " << ent << std::endl;
					held_tool = ent;
					break;
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
		Position* tool_pos = component_manager->get_editable_component_data<Position>(held_tool);

		tool_pos->x = evt->position.x;
		tool_pos->y = evt->position.y;
	}
}

void ToolMouse::draw(sf::RenderTarget* target) {
	
	sf::CircleShape circle;
	circle.setOutlineColor(sf::Color::Red);
	circle.setOutlineThickness(2);
	circle.setFillColor(sf::Color::Transparent);

	for (auto e=registered_entities.begin(); e != registered_entities.end(); e++) {
		Entity ent = (Entity) *e;
		Collider col = component_manager->get_component_data<Collider>(ent);

		circle.setPosition({col.shape.circle.x, col.shape.circle.y});
		circle.setOrigin({col.shape.circle.radius, col.shape.circle.radius});
		circle.setRadius(col.shape.circle.radius);
		target->draw(circle);
	}

	circle.setPosition({(float)mouseX, (float)mouseY});
	circle.setOrigin({1, 1});
	circle.setRadius(1);
	target->draw(circle);


};

