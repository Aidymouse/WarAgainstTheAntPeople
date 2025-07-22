#pragma once

#include <SDL3/SDL.h>
#include <optional>
#include <util/UtilTypes.hpp>

struct AnimFrame {
	SDL_Texture *texture;
	SDL_FRect rect;
	float duration; // -1 if permanent
	AnimFrame *next_frame;
	xy anchor_point; // Point on the image that will align with the entities position
};
