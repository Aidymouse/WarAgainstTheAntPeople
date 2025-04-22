#include "anim/Anim.hpp"
#include "ecs/ComponentArray.hpp"
#include <SDL3/SDL.h>
#include <cmath>
#include <ecs/ECS.hpp>
#include <engine/Components.hpp>
#include <iostream>
#include <systems/DrawSystem.h>
#include <util/DrawFns.h>

int compare_positions(Position p1, Position p2) {
  // std::cout << p1.z << ", " << p2.z << std::endl;
  if (p1.z > p2.z) {
    std::cout << "(" << p1.z << ", " << p2.z << ")" << std::endl;
    return 1;
  }
  if (p1.z < p2.z) {
    std::cout << "(" << p1.z << ", " << p2.z << ")" << std::endl;
    return -1;
  }

  if (p1.y > p2.y) {
    return 1;
  }
  if (p1.y < p2.y) {
    return -1;
  }

  return 0;
}

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

int compare_reserved_ents(Reserved r1, Reserved r2, ECS *ecs) { return 1; }

void DrawSystem::draw(SDL_Renderer *renderer, ECS *ecs, int num_reserved) {
  ComponentArray<Position> positions =
      *component_manager->get_component_array<Position>();

  // TOO SLOW!!!
  // But it does work.
  // positions.sort(0, positions.get_num_components() - 1, &compare_positions);
  //
  // To keep rendering fast, we're going to assume that all

  // I think, for the sake of gameplay, guys should probably go beneath
  // everything else. Then we can just sort the other stuff. To keep this from
  // being stupid we'll need to make sure guys avoid non-guys as they walk
  // around. Or maybe the bottom half of some sprites can be a background tile.
  //
  // Sort the resered entities by their positions
  std::shared_ptr<ComponentArray<Reserved>> res =
      component_manager->get_component_array<Reserved>();

  // Custom quick sort right here?
  res->sort(0, num_reserved, &compare_reserved_ents, ecs);

  Entity eLimit = 0;
  for (Entity e = 0; e < RESERVED_ENTITIES; e++) {
    // Draw if z < 0
    if (ecs->get_signature_for_entity(e)[COMP_SIG::POSITION] == 0)
      continue;

    Position *pos = component_manager->get_component_data<Position>(e);
    if (pos->z >= 0) {
      eLimit = e + 1;
      break; // Entities are pre-sorted
    }

    Visible *vis = component_manager->get_component_data<Visible>(e);

    // Draw the entity
    SDL_FRect source_rect = vis->frame.rect;
    SDL_FRect target_rect = {std::floor(pos->x + vis->offset.x),
                             std::floor(pos->y + vis->offset.y),
                             vis->frame.rect.w, vis->frame.rect.h};
    // SDL_FRect target_rect = {pos->x, pos->y, 16, 16};
    SDL_RenderTexture(renderer, vis->texture, &source_rect, &target_rect);
  }

  // Draw all guys on lowest level
  for (int i = 0; i < positions.get_num_components(); i++) {
    Entity ent = positions.get_entity_from_idx(i);

    if (ent < RESERVED_ENTITIES)
      continue;

    // Position *pos = component_manager->get_component_data<Position>(ent);
    Position pos = positions.get_data_from_idx(i);
    Visible *vis = component_manager->get_component_data<Visible>(ent);
    // pos->x += 0.01;
    // std::cout << "Draw Pos [" << ent << "] " << pos->x << ", " << pos->y
    //<< std::endl;
    // std::cout << "Drawing Texture " << vis.texture << std::endl;

    // if (ecs->get_signature_for_entity(ent)[COMP_SIG::COLLIDER] == 1) {
    // Collider c = *component_manager->get_component_data<Collider>(ent);

    // if (c.type == CollisionShapeType::CIRCLE) {
    // SDL_Render
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // DrawFns::RenderCircle(renderer, c.shape.circle.x, c.shape.circle.y,
    // c.shape.circle.radius);
    // }
    // }

    SDL_FRect source_rect = vis->frame.rect;
    SDL_FRect target_rect = {std::floor(pos.x + vis->offset.x),
                             std::floor(pos.y + vis->offset.y),
                             vis->frame.rect.w, vis->frame.rect.h};
    // SDL_FRect target_rect = {pos->x, pos->y, 16, 16};
    SDL_RenderTexture(renderer, vis->texture, &source_rect, &target_rect);
  }

  for (Entity e = eLimit; e < RESERVED_ENTITIES; e++) {
    // Draw if z >= 1
    if (ecs->get_signature_for_entity(e)[COMP_SIG::POSITION] == 0)
      break;

    Position *pos = component_manager->get_component_data<Position>(e);
    Visible *vis = component_manager->get_component_data<Visible>(e);

    // Draw the entity
    SDL_FRect source_rect = vis->frame.rect;
    SDL_FRect target_rect = {std::floor(pos->x + vis->offset.x),
                             std::floor(pos->y + vis->offset.y),
                             vis->frame.rect.w, vis->frame.rect.h};
    // SDL_FRect target_rect = {pos->x, pos->y, 16, 16};
    SDL_RenderTexture(renderer, vis->texture, &source_rect, &target_rect);
  }
}
