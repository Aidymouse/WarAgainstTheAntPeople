#pragma once


#include <SFML/Graphics.hpp>

#include <engine/GameState.h>
#include <engine/CollisionGrid.h>

#include <entity/Entity.h>
#include <entity/Mallet.h>

class MainState : public GameState {

	CollisionGrid main_grid; // TEMP, should be private at some point
	
	Mallet mallet;
	Tool* grabbed_tool = NULL;

public:
	MainState();

	
	void load() override;
	void handle_event(const std::optional<sf::Event> event) override;
	void update(float dt) override;
	void draw(sf::RenderTarget* render_target) override;

};
