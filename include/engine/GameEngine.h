#pragma once
#include "engine/CollisionGrid.h"
#include <engine/MainState.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <engine/GameState.h>
#include <memory>
#include <SFML/Graphics.hpp>
#include <entity/Entity.h>

class GameEngine {


public:
	GameEngine();
	void run();

	MainState main_state;
	GameState* current_state;
	sf::RenderWindow window;
	sf::Clock clock;

};
