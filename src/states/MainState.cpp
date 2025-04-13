#include "systems/CollisionHandlerSystem.h"
#include "systems/PersuingSystem.h"
#include "systems/TransformSystem.h"
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <states/MainState.h>

#include <ecs/ECS.hpp>
#include <engine/CollisionGrid.h>
#include <systems/CollisionHandlerSystem.h>
#include <systems/DrawSystem.h>
#include <systems/ToolMouse.h>

#include <data/TextureStore.hpp>
#include <engine/Components.hpp>

#include <ProjectConfig.h>

Entity create_guy(ECS *ecs) {
  Entity e = ecs->add_entity();
  //std::cout << "Adding guy with ID " << e << std::endl;

  float pos_x = (float)(rand() % 800);
  float pos_y = (float)(rand() % 600);
  ecs->add_component_to_entity<Position>(e, {pos_x, pos_y});

  Visible guy_vis;
  guy_vis.sprite = std::make_shared<sf::Sprite>(TextureStore::GUY);
  guy_vis.sprite->setPosition({pos_x, pos_y});
  guy_vis.sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));

  ecs->add_component_to_entity<Visible>(e, guy_vis);
  ecs->add_component_to_entity<Smashable>(e, {});
  ecs->add_component_to_entity<ScanningFor>(e, {SCAN_VALUES::SCRAP});
  ecs->add_component_to_entity<Carrier>(e, {NULL});
  ecs->add_component_to_entity<Transform>(e, {0, 0 ,0});

  return e;
};

Entity create_scrap(ECS *ecs) {
  Entity scrap = ecs->add_entity();

  float pos_x = (float)(rand() % 800);
  float pos_y = (float)(rand() % 600);

  ecs->add_component_to_entity<Position>(scrap, {pos_x, pos_y});

  Visible scrap_vis;
  scrap_vis.sprite = std::make_shared<sf::Sprite>(TextureStore::SCRAP);
  scrap_vis.sprite->setPosition({pos_x, pos_y});
  scrap_vis.sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));

  ecs->add_component_to_entity<Visible>(scrap, scrap_vis);
  ecs->add_component_to_entity<Scannable>(scrap, {SCAN_VALUES::SCRAP});
  ecs->add_component_to_entity<Carryable>(scrap, {NULL});

  return scrap;
};

MainState::MainState() {
  // ECS main_ecs;

  /** Set up Systems */
  COMP_SIG sigs[2] = {COMP_SIG::POSITION, COMP_SIG::VISIBLE};
  sys_draw = main_ecs.register_system<DrawSystem>(sigs, 2);

  COMP_SIG toolmouse_sig[2] = {COMP_SIG::COLLIDER, COMP_SIG::CLICKABLE};
  sys_toolmouse = main_ecs.register_system<ToolMouse>(toolmouse_sig, 2);

  COMP_SIG sig_scanning[3] = {COMP_SIG::SCANNING_FOR, COMP_SIG::POSITION,
                              COMP_SIG::TRANSFORM};
  sys_scanning = main_ecs.register_system<ScanningSystem>(sig_scanning, 3);

  COMP_SIG sig_collision[1] = {COMP_SIG::COLLIDER};
  sys_collision_handler =
      main_ecs.register_system<CollisionHandlerSystem>(sig_collision, 1);

  COMP_SIG sig_transform[1] = {COMP_SIG::TRANSFORM};
  sys_transform = main_ecs.register_system<TransformSystem>(sig_transform, 1);

  /** Set up components -- needs to be in order of COMP_SIG */
  main_ecs.register_component<Position>();
  main_ecs.register_component<Visible>();
  main_ecs.register_component<Transform>();
  main_ecs.register_component<Clickable>();

  main_ecs.register_component<Collider>();

  main_ecs.register_component<Smashable>();

  main_ecs.register_component<ScanningFor>();
  main_ecs.register_component<Scannable>();
  main_ecs.register_component<Persuing>();

  main_ecs.register_component<Carrier>();
  main_ecs.register_component<Carryable>();

  main_ecs.register_component<Tool>();

  /** Initial Entities */

  // Mallet
  Entity mallet_id = main_ecs.add_entity();
  main_ecs.add_component_to_entity<Tool>(mallet_id, {0});
  Visible mallet_visible;
  float mallet_x = rand() % 800;
  float mallet_y = rand() % 600;
  mallet_visible.sprite = std::make_shared<sf::Sprite>(TextureStore::MALLET);
  mallet_visible.sprite->setPosition({mallet_x, mallet_y});
  mallet_visible.sprite->setTextureRect(sf::IntRect({0, 0}, {32, 32}));
  mallet_visible.sprite->setOrigin({16, 16});
  main_ecs.add_component_to_entity<Visible>(mallet_id, mallet_visible);
  main_ecs.add_component_to_entity<Position>(mallet_id, {mallet_x, mallet_y});
  main_ecs.add_component_to_entity<Collider>(
      mallet_id, {CollisionShapeType::CIRCLE, {mallet_x, mallet_y, 16}, 0});
  main_ecs.add_component_to_entity<Clickable>(mallet_id, {});

  // Guys
  for (int i = 0; i < 10; i++) {
    create_guy(&main_ecs);
  }

  for (int i = 0; i < 10; i++) {
    create_scrap(&main_ecs);
  }
}

void MainState::handle_click(const sf::Event::MouseButtonPressed *evt) {
  sys_toolmouse->handle_click(evt);
}

void MainState::handle_mousemove(const sf::Event::MouseMoved *evt) {
  sys_toolmouse->handle_mousemove(evt);
}

void MainState::update(float dt) {

  sys_transform->update(dt, &main_grid);

  sys_scanning->update(dt, &main_ecs);
  //sys_draw->update(dt, &main_ecs);
}

void MainState::draw(sf::RenderTarget *target) {
  // sf::Texture guy_tex("../resources/graphics/guy sheet.png");
  /*sf::Sprite guy(guy_tex);*/
  /*guy.setPosition({100, 100});*/
  /*target->draw(guy);*/

  sys_draw->draw(target);
  sys_toolmouse->draw(target);

  main_grid.debug_draw_grid(target);
}
