#include <SDL3/SDL.h>
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
}

void DrawSystem::draw(SDL_Renderer *renderer) {
  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {
    Entity ent = (Entity)*e;
    // std::cout << "Drawing " << ent << std::endl;

    Visible vis = *component_manager->get_component_data<Visible>(ent);
    Position *pos = component_manager->get_component_data<Position>(ent);

    // pos->x += 0.01;
    // std::cout << "Draw Pos [" << ent << "] " << pos->x << ", " << pos->y
    //<< std::endl;
    // std::cout << "Drawing Texture " << vis.texture << std::endl;

    SDL_FRect source_rect = vis.frame;
    SDL_FRect target_rect = {pos->x, pos->y, 16, 16};
    SDL_RenderTexture(renderer, vis.texture, &source_rect, &target_rect);
  }
}
