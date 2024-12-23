#pragma once
struct Entity {
	unsigned int id;
	int x;
	int y;
	unsigned int animation_frame;
	//unsigned int cellId; // First four bits = cell X, last four = cell Y -- Multiple cells ..?
};

enum anim_Guy { // First four bytes are x coordinate, last four are y coordinate. Yes, this means the maximum texture image is 32767 frames wide and tall. Sorry.
	NORM1 = 0 + 0,
	NORM2 = (1 * 32767) + 0,
	FIRE1 = 0 + 1
};
