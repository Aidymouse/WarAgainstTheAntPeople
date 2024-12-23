#include <engine/GameEngine.h>
#include <iostream>
#include <entity/Entity.h>
#include <engine/MenuState.h>
#include <memory>

#include <SFML/Graphics.hpp>

class GameEngine;

GameEngine::GameEngine() {
	MenuState m = MenuState();

	Entity guys[100];

	guys[0] = { 1, 0, 0 };

	//std::cout << guys[0].id << ", " << guys[1].id << std::endl;

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

	std::cout << "Would run window" << std::endl;
	   while (window.isOpen())
	   {
	while (const std::optional event = window.pollEvent())
	{
	    if (event->is<sf::Event::Closed>())
	    {
		window.close();
	    }
	}

	window.clear(sf::Color::White);
	window.display();
	   }

}
