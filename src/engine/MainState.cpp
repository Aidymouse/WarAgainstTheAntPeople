#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <stdlib.h>
#include <iostream>


#include <engine/MainState.h>
#include <entity/Entity.h>
#include <entity/Guy.h>
#include <engine/MenuState.h>

#include <data/EntityAttributes.h>
#include <data/TextureBank.h>

#include <SFML/Graphics.hpp>


MainState::MainState() : GameState::GameState() {

	//const sf::Texture testTex("../resources/graphics/guy sheet.png");

	Guy g;
	g.animation_frame = frames_Guy::NORM1;

	for (int i=0; i<2500; i++) {

		g.x = rand() % 800;
		g.y = rand() % 600;
		//std::cout << g.x << std::endl;
		main_grid.insert_guy(g);
	}

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
	sf::Sprite guy_sprite(TextureBank::guy);
	guy_sprite.setOrigin({EntityAttributes::Guy.origin_x, EntityAttributes::Guy.origin_y });

	for (int cell_idx = 0; cell_idx<cell_count; cell_idx++) {
		CollisionCell* cell = main_grid.get_cell(cell_idx);

		int guy_count = cell->get_guy_count();
		sf::IntRect guy_rect({0, 0}, {16, 16});

		for (int guy_idx=0; guy_idx<guy_count; guy_idx++) {
			Guy* guy = cell->get_guy(guy_idx);
			//std::cout << "Guy " << guy_idx << ": " << guy->x << ", " << guy->y << std::endl;
			guy_sprite.setTextureRect({{0, 0}, {16, 16}});
			guy_sprite.setPosition({(float) guy->x, (float) guy->y});
			target->draw(guy_sprite);
		}
		
	}
}
