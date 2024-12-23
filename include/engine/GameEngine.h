#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <engine/GameState.h>
#include <memory>
#include <SFML/Graphics.hpp>

class GameEngine {
public:
	GameEngine();
	void init();
	void update();
	void run();

	std::shared_ptr<GameState> currentState;
	sf::RenderWindow window;
};
