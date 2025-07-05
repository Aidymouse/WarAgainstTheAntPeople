#pragma once

#include <SDL3/SDL.h>
#include <optional>

struct AnimFrame {
	SDL_FRect rect;
	float duration; // -1 if permanent
	AnimFrame *next_frame;
	int offset_x;
	int offset_y;
};
