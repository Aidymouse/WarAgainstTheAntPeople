#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <cstdlib>
#include <ctime>
#include <engine/MainState.h>
#include <iostream>
#include <entity/Entity.h>
#include <entity/Guy.h>
#include <engine/MenuState.h>
#include <memory>

#include <SFML/Graphics.hpp>


MainState::MainState() : GameState::GameState() {
	std::srand(time(0));

	Guy g;
	g.animation_frame = anim_Guy::NORM1;
	g.anchor_x = 8;
	g.anchor_y = 16;

	for (int i=0; i<2500; i++) {
		g.x = std::rand() % 800;
		g.y = std::rand() % 600;
	}

	main_grid.insert_guy(g);
}


void MainState::update(float dt) {
	// Tools
	
	// Other entities
	
	// Guys + Check for Collisions + update some stuff
	
	// Apply updates to entities
}

void MainState::load() {}

void MainState::draw(sf::RenderTarget* target) {
	target->clear(sf::Color::White);

	int cell_count = main_grid.get_cell_count();

	for (int cell_idx = 0; cell_idx<cell_count; cell_idx++) {
		CollisionCell* cell = main_grid.get_cell(cell_idx);

		
		
	}
}
