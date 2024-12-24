#pragma once
struct Entity {
	unsigned short cells[4]; // Cell indexes

	int x;
	int y;

	unsigned short id;
	unsigned short animation_frame;

};

enum anim_Guy { // First four bytes are x coordinate, last four are y coordinate. Yes, this means the maximum texture image is 32767 frames wide and tall. Sorry.
	NORM1 = 0 + 0,
	NORM2 = (1 * 32767) + 0,
	FIRE1 = 0 + 1
};
