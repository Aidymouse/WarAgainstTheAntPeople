#pragma once

#include <engine/StateManager.h>
#include <SFML/Graphics.hpp>

class Engine {

	StateManager state_manager;
	sf::RenderWindow window;
	sf::Clock clock;

public:
	Engine();
	void run();
};
