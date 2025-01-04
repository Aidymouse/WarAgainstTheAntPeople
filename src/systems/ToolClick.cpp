#include <SFML/Window/Event.hpp>
#include <iostream>
#include <systems/ToolClick.h>

void ToolClick::handle_click(const sf::Event::MouseButtonPressed* evt) {
	std::cout << "Tool Clicking" << std::endl;
}

