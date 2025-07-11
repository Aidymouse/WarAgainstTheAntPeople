#pragma once

#include <SDL3/SDL.h>
#include <ecs/ECS.hpp>
#include <ecs/System.hpp>

class DrawSystem : public System {
public:
  void update(float dt, ECS *ecs);
  void draw(SDL_Renderer *renderer, ECS *ecs);
	
	// Run inside draw
	void sorted_draw(SDL_Renderer, ECS *ecs);
	void unsorted_draw(SDL_Renderer, ECS *ecs);


	// TODO
	void draw_decorations(SDL_Renderer, ECS *ecs);
};
