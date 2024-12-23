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

}

void GameEngine::init() {
	// Load window
	// Texture cache ?
}

void GameEngine::run() {

	sf::Texture guyTexture("../resources/graphics/guy sheet.png");

	sf::VertexArray guyArray(sf::PrimitiveType::Triangles, 6*100);
	int numGuys = 0;

	for (int i=0; i<100; i++) {
		guys[i].id = i;
		guys[i].x = i*2;
		guys[i].y = i*2;
		guys[i].animation_frame = anim_Guy::NORM1;
		numGuys++;
	}
	//guys[0] = { 1, 0, 0, anim_Guy::FIRE1};


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

		for (int i=0; i<numGuys; i++) {
			int guy_vertex_idx = i*6;
			guyArray[guy_vertex_idx].position = sf::Vector2f(guys[i].x, guys[i].y);
			guyArray[guy_vertex_idx+1].position = sf::Vector2f(guys[i].x, guys[i].y+15);
			guyArray[guy_vertex_idx+2].position = sf::Vector2f(guys[i].x+15, guys[i].y+15);

			guyArray[guy_vertex_idx+3].position = sf::Vector2f(guys[i].x+15, guys[i].y+15);
			guyArray[guy_vertex_idx+4].position = sf::Vector2f(guys[i].x+15, guys[i].y);
			guyArray[guy_vertex_idx+5].position = sf::Vector2f(guys[i].x, guys[i].y);

			int tex_y = guys[i].animation_frame % 32767; // Unsigned
			int tex_x = ((guys[i].animation_frame - tex_y) / 32767) * 16;
			tex_y *= 16;

			//std::cout << "X " << tex_x << ", Y " << tex_y << std::endl;

			guyArray[guy_vertex_idx].texCoords = sf::Vector2f(tex_x, tex_y);
			guyArray[guy_vertex_idx+1].texCoords = sf::Vector2f(tex_x, tex_y+16);
			guyArray[guy_vertex_idx+2].texCoords = sf::Vector2f(tex_x+16, tex_y+16);

			guyArray[guy_vertex_idx+3].texCoords = sf::Vector2f(tex_x+16, tex_y+16);
			guyArray[guy_vertex_idx+4].texCoords = sf::Vector2f(tex_x+16, tex_y);
			guyArray[guy_vertex_idx+5].texCoords = sf::Vector2f(tex_x, tex_y);
		}

		window.draw(guyArray, &guyTexture);

		window.display();
	}

}
