#include <iostream>

#include <systems/ToolMouse.h>
#include <SFML/Window/Event.hpp>
#include <engine/Components.hpp>

void ToolMouse::handle_click(const sf::Event::MouseButtonPressed* evt) {

	for (auto e=registered_entities.begin(); e != registered_entities.end(); e++) {
		Entity ent = (Entity) *e;

		Collider col = component_manager->get_component_data<Collider>(ent);

	}

	std::cout << "Tool Clicking" << std::endl;

}

