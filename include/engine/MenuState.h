#pragma once
#include <engine/GameState.h>

class MenuState : public GameState {
public:
	void load() override;
	void update() override;
	void draw() override;
};
