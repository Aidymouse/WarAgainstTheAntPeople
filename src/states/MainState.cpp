#include <string>

#include <states/MainState.h>

#include <ecs/ECS.hpp>

#include <SDL3/SDL.h>
#include <data/TextureStore.hpp>
#include <engine/Components.hpp>
#include <systems/DrawSystem.h>

#include <fstream>
#include <iostream>

#include <ProjectConfig.h>

TextureStore &texture_store = TextureStore::getInstance();

void add_guy(ECS *ecs) {

  Visible v = {texture_store.get("guy_sheet"), {0, 0, 16, 16}};
  float x = (float)(rand() % 800);
  float y = (float)(rand() % 600);
  Position p = {x, y, 0};
  Entity g = ecs->add_entity();
  ecs->add_component_to_entity<Visible>(g, v);
  ecs->add_component_to_entity<Position>(g, p);

  std::cout << "Added guy [" << g << "] at " << x << ", " << y << std::endl;
}

MainState::MainState() {
  ECS main_ecs;

  TextureStore &texture_store = TextureStore::getInstance();

  /** Set up Systems */
  Signature draw_sig;
  draw_sig[COMP_SIG::POSITION] = 1;
  draw_sig[COMP_SIG::VISIBLE] = 1;
  sys_draw = main_ecs.register_system<DrawSystem>(draw_sig);

  /** Set up components -- needs to be in order of COMP_SIG */
  main_ecs.register_component<Position>();
  main_ecs.register_component<Visible>();
  // main_ecs.register_component<Tool>();
  // main_ecs.register_component<Clickable>();

  main_ecs.register_component<Collider>();

  main_ecs.register_component<Smashable>();

  // main_ecs.register_component<ScanningFor>();
  // main_ecs.register_component<Scannable>();
  // main_ecs.register_component<Persuing>();

  main_ecs.register_component<Carrier>();
  main_ecs.register_component<Carryable>();

  main_ecs.register_component<Tool>();

  /** Initial Entities */

  // std::ifstream guybmp(std::string(GRAPHICS_PATH).append("guy_sheet.bmp"));

  // guybmp.close();
  //  guy_surface = SDL_LoadBmp();
  //   Mallet

  // Guys
  for (int g = 0; g < 1000; g++) {
    add_guy(&main_ecs);
  }
}

MainState::~MainState() {}

void MainState::handle_click() {}

void MainState::handle_mousemove() {}

void MainState::update(float dt) {}

void MainState::draw(SDL_Renderer *renderer) { sys_draw->draw(renderer); }
