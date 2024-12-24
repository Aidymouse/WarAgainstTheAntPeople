#pragma once
#include "engine/CollisionGrid.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <engine/GameState.h>
#include <memory>
#include <SFML/Graphics.hpp>
#include <entity/Entity.h>

class GameEngine {

public:
	GameEngine();
	void init();
	void update();
	void run();

	std::shared_ptr<GameState> currentState;
	sf::RenderWindow window;
	Entity guys[100];
};
