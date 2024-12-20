#include <GameEngine.h>
#include <iostream>

class GameEngine;

GameEngine::GameEngine() { }

void GameEngine::update() {
	std::cout << "Game Engine Update" << std::endl;
}

