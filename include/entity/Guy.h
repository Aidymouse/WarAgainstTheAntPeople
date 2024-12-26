#pragma once

#include <entity/Entity.h>

struct Guy {
	Entity* wielding;

	float vel_x;
	float vel_y;

	short x;
	short y;

	unsigned short id;
	unsigned short animation_frame;

	unsigned char anchor_x;
	unsigned char anchor_y;
};

enum states_Guy {
};

enum anim_Guy { // First four bytes are x coordinate, last four are y coordinate. Yes, this means the maximum texture image is 32767 frames wide and tall. Sorry.
	NORM1 = 0 + 0,
	NORM2 = (1 * 32767) + 0,
	FIRE1 = 0 + 1
};
