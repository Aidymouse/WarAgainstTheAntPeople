#pragma once
#include <GameState.h>
#include <memory>

class GameEngine {
public:
	GameEngine();
	void update();

	std::shared_ptr<GameState> currentState;
};
