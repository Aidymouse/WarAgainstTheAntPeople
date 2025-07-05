#include "anim/Anim.hpp"
#include "ecs/ComponentArray.hpp"
#include <SDL3/SDL.h>
#include <cmath>
#include <components/Components.hpp>
#include <ecs/ECS.hpp>
#include <iostream>
#include <systems/DrawSystem.h>
#include <util/DrawFns.h>

void DrawSystem::update(float dt, ECS *ecs) {

  // Update animation timer
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
}

// This simplistic draw system just draws everything visible.
// There is a counterpart, the sorted draw system, that sorts before it draws
// Typically, this is used to draw guys.
void DrawSystem::draw(SDL_Renderer *renderer, ECS *ecs) {

  // To keep rendering fast, we're going to assume that all

  std::shared_ptr<ComponentArray<Visible>> visibles = component_manager->get_component_array<Visible>();
  std::shared_ptr<ComponentArray<Position>> positions = component_manager->get_component_array<Position>();

  // Draw all visibles
  for (int i = 0; i < visibles->get_num_components(); i++) {

    Entity ent = visibles->get_entity_from_idx(i);
    Visible vis = visibles->get_data_from_idx(i);

    // Position *pos = component_manager->get_component_data<Position>(ent);
    Position *pos = positions->get_data(ent);
    // Visible *vis = component_manager->get_component_data<Visible>(ent);

    SDL_FRect source_rect = vis.frame.rect;
    SDL_FRect target_rect = {std::floor(pos->x + vis.offset.x + vis.frame.offset_x),
                             std::floor(pos->y + vis.offset.y + vis.frame.offset_y),
                             vis.frame.rect.w, vis.frame.rect.h};
    // SDL_FRect target_rect = {pos->x, pos->y, 16, 16};
    SDL_RenderTexture(renderer, vis.texture, &source_rect, &target_rect);
  }
}
