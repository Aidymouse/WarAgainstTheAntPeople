#pragma once

class GameState {
public:
	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	virtual void handle_click() {};
	virtual void handle_mousemove() {};

	virtual void leave_state() = 0;
	virtual void enter_state() = 0;
};
