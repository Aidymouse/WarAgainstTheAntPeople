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


MainState::MainState() {
	std::srand(time(0));

	window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Evil Pikmin (Working title)");
	window.setFramerateLimit(144);

	Guy g;
	g.animation_frame = anim_Guy::NORM1;
	g.anchor_x = 8;
	g.anchor_y = 16;

	for (int i=0; i<2500; i++) {
		g.x = std::rand() % 800;
		g.y = std::rand() % 600;
	}

}

void MainState::update(float dt) {

	// Tools
	
	// Other entities
	
	// Guys + Check for Collisions + update some stuff
	
	// Apply updates to entities
}

void MainState::run() {

	sf::Texture guyTexture("../resources/graphics/guy sheet.png");

	sf::Sprite guy(guyTexture);
	
	sf::Clock clock;
	float delta_time = 0;

	while (window.isOpen()) {

		while (const std::optional event = window.pollEvent())
		{
		    if (event->is<sf::Event::Closed>())
		    {
			window.close();
		    }
		}

		/* Update */
		update(delta_time);

		// Update Guys


		/* Draw */
		window.clear(sf::Color::White);

		for (cell_id cell_id = 0; cell_id < 192; cell_id++) {
			/*Guy* cell_ents = main_grid.get_entities(cell_id);*/
			/*int cell_count = main_grid.get_count(cell_id);*/

			/*for (int ent_idx=0; ent_idx<cell_count; ent_idx++) {*/
			/*	Guy ent = cell_ents[ent_idx];*/
			/**/
			/*	short tex_tile_y = ent.animation_frame % 32767;*/
			/*	short tex_tile_x = (ent.animation_frame - tex_tile_y) / 32767;*/
			/**/
			/*	guy.setPosition(sf::Vector2f(ent.x-ent.anchor_x, ent.y-ent.anchor_y));*/
			/*	guy.setTextureRect(sf::IntRect(sf::Vector2i(tex_tile_x*16, tex_tile_y*16), sf::Vector2i(16, 16)));*/
			/*	window.draw(guy);*/
			/*}*/
		}

		window.display();

		float cur_time = clock.restart().asSeconds();
		float fps = 1.f / (cur_time);
		delta_time = cur_time;

		std::cout << "FPS: " << fps << std::endl;
	}

}
