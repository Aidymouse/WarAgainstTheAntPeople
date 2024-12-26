#pragma once
#include "engine/CollisionGrid.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <engine/GameState.h>
#include <memory>
#include <SFML/Graphics.hpp>
#include <entity/Entity.h>

class MainState : public GameState {

	std::vector<Entity> entities;

public:
	MainState();
	void init();
	void update(float delta_time);
	void run();

	std::unique_ptr<GameState> currentState;
	sf::RenderWindow window;

	CollisionGrid main_grid;
};
