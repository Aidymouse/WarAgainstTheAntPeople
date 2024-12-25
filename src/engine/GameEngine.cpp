#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <engine/GameEngine.h>
#include <iostream>
#include <entity/Entity.h>
#include <engine/MenuState.h>
#include <memory>

#include <SFML/Graphics.hpp>

class GameEngine;



GameEngine::GameEngine() {
	MenuState m = MenuState();

	//std::cout << guys[0].id << ", " << guys[1].id << std::endl;

	//testGuy = sf::Sprite(guyTex);
	//sf::Sprite testGuy(guyTex);
	//testGuy.setTexture(guyTex);
	//std::shared_ptr<GameState> currentState = std::make_shared<MenuState>(m);
	currentState = std::make_shared<MenuState>(m);


	window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Evil Pikmin (Working title)");
	window.setFramerateLimit(144);

	Entity g;
	g.x = 100;
	g.y = 100;
	g.animation_frame = anim_Guy::NORM2;

	main_grid.insert_entity(g);

	g.x = 120;
	g.y = 100;
	g.animation_frame = anim_Guy::FIRE1;
	main_grid.insert_entity(g);

}

void GameEngine::init() {
	// Load window
	// Texture cache ?
}

void GameEngine::run() {

	sf::Texture guyTexture("../resources/graphics/guy sheet.png");

	sf::Sprite guy(guyTexture);


	while (window.isOpen()) {

		while (const std::optional event = window.pollEvent())
		{
		    if (event->is<sf::Event::Closed>())
		    {
			window.close();
		    }
		}

		/* Update */

		// Update Guys

		/* Draw */
		window.clear(sf::Color::White);

		for (cell_id cell_id = 0; cell_id < 192; cell_id++) {
			Entity* cell_ents = main_grid.get_entities(cell_id);
			int cell_count = main_grid.get_count(cell_id);

			for (int ent_idx=0; ent_idx<cell_count; ent_idx++) {
				Entity ent = cell_ents[ent_idx];

				short tex_tile_y = ent.animation_frame % 32767;
				short tex_tile_x = (ent.animation_frame - tex_tile_y) / 32767;

				guy.setPosition(sf::Vector2f(ent.x, ent.y));
				guy.setTextureRect(sf::IntRect(sf::Vector2i(tex_tile_x*16, tex_tile_y*16), sf::Vector2i(16, 16)));
				window.draw(guy);
			}
		}


		// Display everythign
		window.display();
	}

}
