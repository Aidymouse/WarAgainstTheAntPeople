#include "anim/Anim.hpp"
#include "ecs/ComponentArray.hpp"
#include <SDL3/SDL.h>
#include <cmath>
#include <components/Components.hpp>
#include <ecs/ECS.hpp>
#include <iostream>
#include <systems/DrawSystem.h>
#include <util/DrawFns.h>

static int compare_visibles_by_position(SortedVisible v1, SortedVisible v2,
                                        Entity e1, Entity e2, ECS *ecs) {
  Position p1 = *ecs->get_component_for_entity<Position>(e1);
  Position p2 = *ecs->get_component_for_entity<Position>(e2);

  if (p1.z > p2.z) {
    return 1;
  }

  return 0;
}

void update_anim_timer(float dt, float& anim_timer, AnimFrame& frame) {
	if (anim_timer != -1 && frame.duration != -1) {

		anim_timer += dt;

		if (anim_timer > frame.duration) {

			anim_timer -= frame.duration;
        	// TODO: more robustness with skipping frames. There could potentially be multiple frames skipped a frame, current set up will only ever get one

        	if (frame.next_frame != nullptr) {
          		//AnimFrame a = *frame.next_frame;
          		frame = *(frame.next_frame);
        	} else {
          		std::cout << "Animation timer ran out but no next frame! Locking." << std::endl;
          		anim_timer = -1;
        	}
		}
	}
}

// The draw system is responsible for two types of drawable entities - sorted and unsorted
// It also manages putting things in sorted vs unsorted
// TODO one day it will handle decorations too
void DrawSystem::update(float dt, ECS *ecs) {

	/** Update animation timers */
	// Update Decorations
	std::shared_ptr<ComponentArray<Decoration>> decorations = component_manager->get_component_array<Decoration>();
  	for (int i = 0; i < decorations->get_num_components(); i++) {

		Entity ent = decorations->get_entity_from_idx(i);
		Decoration *d_vis = decorations->get_editable_data_from_idx(i);
		
	}

	std::shared_ptr<ComponentArray<Visible>> comp_visible = component_manager->get_component_array<Visible>();
  	for (int i = 0; i < comp_visible->get_num_components(); i++) {

		Entity ent = comp_visible->get_entity_from_idx(i);
		Visible *vis = comp_visible->get_editable_data_from_idx(i);
		
		update_anim_timer(dt, vis->anim_timer, vis->frame);
	}

	// Sort the sorted drawables
	std::shared_ptr<ComponentArray<SortedVisible>> visibles = component_manager->get_component_array<SortedVisible>();
	visibles->insertion_sort(&compare_visibles_by_position, ecs);
}


void render_component(SDL_Renderer *renderer, ECS *ecs, SDL_Texture* texture, AnimFrame& frame, Position& pos, xy& offset) {
	/** Draw Shadow if in air */
	if (pos.z > 0) {
    	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
		int shadow_radius = frame.rect.w/1.5 - pos.z*5;
		if (shadow_radius < 10) { shadow_radius = 10; }
		DrawFns::RenderFilledCircle(renderer, pos.x, pos.y, shadow_radius);
	}

    SDL_FRect source_rect = frame.rect;
    SDL_FRect target_rect = {std::floor(pos.x + offset.x + frame.offset_x),
                             std::floor(pos.y + offset.y + frame.offset_y - pos.z),
                             frame.rect.w, frame.rect.h};
    // SDL_FRect target_rect = {pos->x, pos->y, 16, 16};
    SDL_RenderTexture(renderer, texture, &source_rect, &target_rect);
}




// This simplistic draw system just draws everything visible. It sorts things marked sortable
void DrawSystem::draw(SDL_Renderer *renderer, ECS *ecs) {


	// Decorations
/*
	std::shared_ptr<ComponentArray<Decoration>> decorations = component_manager->get_component_array<Decoration>();
  	for (int i = 0; i < decorations->get_num_components(); i++) {

		Entity ent = decorations->get_entity_from_idx(i);
		Decoration d_vis = decorations->get_data_from_idx(i);

		Visible vis;
		vis.texture = d_vis.texture;
		vis.frame = d_vis.frame;
		vis.offset.x = d_vis.offset.x;
		vis.offset.y = d_vis.offset.y;

		Position *pos = ecs->get_component_for_entity<Position>(ent);
		render_component(renderer, ecs, vis, pos);
	}
*/


  std::shared_ptr<ComponentArray<Visible>> visibles = component_manager->get_component_array<Visible>();

  for (int i = 0; i < visibles->get_num_components(); i++) {

    Entity ent = visibles->get_entity_from_idx(i);
    Visible vis = visibles->get_data_from_idx(i);
    Position pos = *ecs->get_component_for_entity<Position>(ent);

	render_component(renderer, ecs, vis.texture, vis.frame, pos, vis.offset);
  }

  std::shared_ptr<ComponentArray<SortedVisible>> sorted_visibles = component_manager->get_component_array<SortedVisible>();

  for (int i = 0; i < sorted_visibles->get_num_components(); i++) {

    Entity ent = sorted_visibles->get_entity_from_idx(i);
    SortedVisible s_vis = sorted_visibles->get_data_from_idx(i);
    Position pos = *ecs->get_component_for_entity<Position>(ent);

	render_component(renderer, ecs, s_vis.texture, s_vis.frame, pos, s_vis.offset);
  }

}


