#include <GameEngine.h>
#include <iostream>
#include <MenuState.h>
#include <memory>

class GameEngine;

GameEngine::GameEngine() {
	MenuState m = MenuState();

	//std::shared_ptr<GameState> currentState = std::make_shared<MenuState>(m);
	currentState = std::make_shared<MenuState>(m);


}

void GameEngine::update() {
	std::cout << "Game Engine Update" << std::endl;
	currentState->update();
}

