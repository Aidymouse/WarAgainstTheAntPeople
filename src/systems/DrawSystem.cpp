#include "anim/Anim.hpp"
#include <SDL3/SDL.h>
#include <cmath>
#include <ecs/ECS.hpp>
#include <engine/Components.hpp>
#include <iostream>
#include <systems/DrawSystem.h>

void DrawSystem::update(float dt, ECS *ecs) {
  /*for (auto e=registered_entities.begin(); e != registered_entities.end();
   * e++) {*/
  /*	Entity ent = (Entity) *e;*/
  /**/
  /*	Visible vis = component_manager->get_component_data<Visible>(ent);*/
  /*}*/
  // Sort entities
  //

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

void DrawSystem::draw(SDL_Renderer *renderer, ECS *ecs) {
  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {
    Entity ent = (Entity)*e;
    // std::cout << "Drawing " << ent << std::endl;

    Visible *vis = component_manager->get_component_data<Visible>(ent);
    Position *pos = component_manager->get_component_data<Position>(ent);

    // pos->x += 0.01;
    // std::cout << "Draw Pos [" << ent << "] " << pos->x << ", " << pos->y
    //<< std::endl;
    // std::cout << "Drawing Texture " << vis.texture << std::endl;

    if (ecs->get_signature_for_entity(ent)[COMP_SIG::COLLIDER] == 1) {
      Collider c = *component_manager->get_component_data<Collider>(ent);

      if (c.type == CollisionShapeType::CIRCLE) {
        //SDL_Render
      }
    }

    

    SDL_FRect source_rect = vis->frame.rect;
    SDL_FRect target_rect = {std::floor(pos->x), std::floor(pos->y), 16, 16};
    // SDL_FRect target_rect = {pos->x, pos->y, 16, 16};
    SDL_RenderTexture(renderer, vis->texture, &source_rect, &target_rect);
  }
}
