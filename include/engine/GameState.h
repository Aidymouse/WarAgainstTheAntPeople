#pragma once

class GameState {
public:
	virtual void load() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};
