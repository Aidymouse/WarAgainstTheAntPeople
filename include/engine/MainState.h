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

	CollisionGrid main_grid; // TEMP
	
	void load() override;
	void update(float dt) override;
	void draw(sf::RenderTarget* render_target) override;

};
