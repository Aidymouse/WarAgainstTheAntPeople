#pragma once

#include <engine/GameState.h>
#include <memory>

class StateManager {

	std::shared_ptr<GameState> current_state;

public:
	std::shared_ptr<GameState> get_current_state() { return current_state; }
	void set_state(std::shared_ptr<GameState> state) { current_state = state; }
	//void switch_state(GameState next_state);
};
