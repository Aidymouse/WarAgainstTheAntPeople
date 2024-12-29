#include <SFML/Graphics/RenderTarget.hpp>
#include <engine/MenuState.h>
#include <iostream>

void MenuState::load() {
}

void MenuState::update(float dt) {
	std::cout << "Menu State, UPDATE!" << std::endl;

}

void MenuState::draw(sf::RenderTarget* render_target) {
	std::cout << "Menu State, DRAW!" << std::endl;
}

