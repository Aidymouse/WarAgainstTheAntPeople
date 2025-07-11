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

// The draw system is responsible for two types of drawable entities - sorted and unsorted
// It also manages putting things in sorted vs unsorted
// TODO one day it will handle decorations too
void DrawSystem::update(float dt, ECS *ecs) {

  // Update animation timers TODO
  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {
    Entity ent = (Entity)*e;
    Visible *vis = component_manager->get_component_data<Visible>(ent);
    if (vis->anim_timer != -1 && vis->frame.duration != -1) {

      vis->anim_timer += dt;

      if (vis->anim_timer > vis->frame.duration) {

        vis->anim_timer -= vis->frame.duration;
        // TODO: more robustness with skipping frames

        if (vis->frame.next_frame != nullptr) {
          AnimFrame a = *vis->frame.next_frame;
          vis->frame = *(vis->frame.next_frame);
        } else {
          std::cout << "Animation timer ran out but no next frame! Locking."
                    << std::endl;
          vis->anim_timer = -1;
        }
      }
    }
  }

	// Sort the sorted drawables
  std::shared_ptr<ComponentArray<SortedVisible>> visibles = component_manager->get_component_array<SortedVisible>();
  visibles->insertion_sort(&compare_visibles_by_position, ecs);
}


void render_component(SDL_Renderer *renderer, ECS *ecs, Visible vis, Position *pos) {
	/** Draw Shadow if in air */
	if (pos->z > 0) {
    	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
		int shadow_radius = vis.frame.rect.w/1.5 - pos->z*5;
		if (shadow_radius < 10) { shadow_radius = 10; }
		DrawFns::RenderFilledCircle(renderer, pos->x, pos->y, shadow_radius);
	}

    SDL_FRect source_rect = vis.frame.rect;
    SDL_FRect target_rect = {std::floor(pos->x + vis.offset.x + vis.frame.offset_x),
                             std::floor(pos->y + vis.offset.y + vis.frame.offset_y - pos->z),
                             vis.frame.rect.w, vis.frame.rect.h};
    // SDL_FRect target_rect = {pos->x, pos->y, 16, 16};
    SDL_RenderTexture(renderer, vis.texture, &source_rect, &target_rect);
}




// This simplistic draw system just draws everything visible. It sorts things marked sortable
void DrawSystem::draw(SDL_Renderer *renderer, ECS *ecs) {

  std::shared_ptr<ComponentArray<Visible>> visibles = component_manager->get_component_array<Visible>();
  //std::shared_ptr<ComponentArray<Position>> positions = component_manager->get_component_array<Position>();

	//std::shared_ptr<ComponentArray<Visible>> sorted_visibles_c = std::static_pointer_cast<ComponentArray<Visible>>(sorted_visibles);

  for (int i = 0; i < visibles->get_num_components(); i++) {

    Entity ent = visibles->get_entity_from_idx(i);
    Visible vis = visibles->get_data_from_idx(i);
    Position *pos = ecs->get_component_for_entity<Position>(ent);

	render_component(renderer, ecs, vis, pos);
  }

/** Idk if this is horribly slow or what but we can convert a visible into a sorted visible pretty easily */
// My biggest worry would be the stack frames calling a func for every entity but surely the component is smart enough to inline here...
	std::shared_ptr<ComponentArray<SortedVisible>> sorted_visibles = component_manager->get_component_array<SortedVisible>();
  for (int i = 0; i < sorted_visibles->get_num_components(); i++) {

    Entity ent = sorted_visibles->get_entity_from_idx(i);
    SortedVisible s_vis = sorted_visibles->get_data_from_idx(i);

	Visible vis;
	vis.texture = s_vis.texture;
	vis.frame = s_vis.frame;
	vis.offset.x = s_vis.offset.x;
	vis.offset.y = s_vis.offset.y;

    Position *pos = ecs->get_component_for_entity<Position>(ent);

	render_component(renderer, ecs, vis, pos);
  }

}

