#include <string>

#include <states/MainState.h>

#include <ecs/ECS.hpp>

#include <data/TextureStore.hpp>
#include <engine/Components.hpp>

#include <ProjectConfig.h>



MainState::MainState() {
  // ECS main_ecs;

  /** Set up Systems */

  /** Set up components -- needs to be in order of COMP_SIG */
  main_ecs.register_component<Position>();
  main_ecs.register_component<Visible>();
  main_ecs.register_component<Tool>();
  main_ecs.register_component<Clickable>();

  main_ecs.register_component<Collider>();
  main_ecs.register_component<ColliderHandler_mallet>();

  main_ecs.register_component<ScanningFor>();
  main_ecs.register_component<Scannable>();
  main_ecs.register_component<Persuing>();

  /** Initial Entities */

  // Mallet

  // Guys
}

void MainState::handle_click() { }

void MainState::handle_mousemove() { }

void MainState::update(float dt) { }

void MainState::draw() {
  // sf::Texture guy_tex("../resources/graphics/guy sheet.png");
  /*sf::Sprite guy(guy_tex);*/
  /*guy.setPosition({100, 100});*/
  /*target->draw(guy);*/

}
