#include "anim/Anim.hpp"
#include "ecs/ComponentArray.hpp"
#include <SDL3/SDL.h>
#include <cmath>
#include <components/Components.hpp>
#include <ecs/ECS.hpp>
#include <iostream>
#include <systems/SortedDrawSystem.h>
#include <util/DrawFns.h>

static int compare_positions(Position p1, Position p2, Entity e1, Entity e2,
                             ECS *ecs) {
  // std::cout << p1.z << ", " << p2.z << std::endl;
  // if (p1->z > p2->z) {
  //   // std::cout << "(" << p1->z << ", " << p2->z << ")" << std::endl;
  //   return 1;
  // }
  if (p1.z > p2.z) {
    // std::cout << "(" << p1->z << ", " << p2->z << ")" << std::endl;
    return 1;
  }
  // if (p1.y > p2.y) {
  //   // std::cout << "(" << p1->z << ", " << p2->z << ")" << std::endl;
  //   return 1;
  // }

  // if (p1.y < p2.y) {
  //   // std::cout << "(" << p1->z << ", " << p2->z << ")" << std::endl;
  //   return -1;
  // }

  // if (p1->y > p2->y) {
  //   return 1;
  // }
  // if (p1->y < p2->y) {
  //   return -1;
  // }

  return 0;
}

static int compare_visibles_by_position(SortedVisible v1, SortedVisible v2,
                                        Entity e1, Entity e2, ECS *ecs) {
  Position p1 = *ecs->get_component_for_entity<Position>(e1);
  Position p2 = *ecs->get_component_for_entity<Position>(e2);

  if (p1.z > p2.z) {
    return 1;
  }

  return 0;
}

void SortedDrawSystem::update(float dt, ECS *ecs) {

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

  // std::shared_ptr<ComponentArray<Position>> positions =
  // component_manager->get_component_array<Position>();
  // positions->insertion_sort(&compare_positions, ecs);

  std::shared_ptr<ComponentArray<SortedVisible>> visibles =
      component_manager->get_component_array<SortedVisible>();
  visibles->insertion_sort(&compare_visibles_by_position, ecs);
}

// void SortedDrawSystem::draw_beneath_0() {
// }

void SortedDrawSystem::draw(SDL_Renderer *renderer, ECS *ecs) {
  std::shared_ptr<ComponentArray<Position>> positions =
      component_manager->get_component_array<Position>();
  std::shared_ptr<ComponentArray<SortedVisible>> visibles =
      component_manager->get_component_array<SortedVisible>();

  // Draw all guys on lowest level
  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {
    Entity ent = (Entity)*e;

    // Position *pos = component_manager->get_component_data<Position>(ent);
    Position *pos = component_manager->get_component_data<Position>(ent);
    SortedVisible *vis =
        component_manager->get_component_data<SortedVisible>(ent);

    SDL_FRect source_rect = vis->frame.rect;
    SDL_FRect target_rect = {std::floor(pos->x + vis->offset.x),
                             std::floor(pos->y + vis->offset.y),
                             vis->frame.rect.w, vis->frame.rect.h};
    // SDL_FRect target_rect = {pos->x, pos->y, 16, 16};
    SDL_RenderTexture(renderer, vis->texture, &source_rect, &target_rect);
  }
}
