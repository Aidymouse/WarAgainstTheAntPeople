#pragma once

#include <ecs/ECS.hpp>
#include <ecs/System.hpp>
#include <SDL3/SDL.h>

class ScanningSystem : public System {
public:
	void update(float dt, ECS *ecs);
	void debug_draw(SDL_Renderer *renderer, ECS *ecs);
};
