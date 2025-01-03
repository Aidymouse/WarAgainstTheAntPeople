#include <SFML/Graphics/Texture.hpp>
#include <ecs/ECS.hpp>
#include <string>
#include <systems/PhysicsSystem.h>
#include <systems/DrawSystem.h>
#include <engine/Components.hpp>

#include <states/MainState.h>
#include <ProjectConfig.h>


std::string G = std::string(GRAPHICS_PATH);
const sf::Texture guy_tex(G.append("guy sheet.png"));

MainState::MainState() {
	ECS main_ecs;

	// Set up Systems
	Signature physics_signature = 0;
	physics_signature[COMP_SIG::POSITION] = 1;
	physics_signature[COMP_SIG::TRANSLATE] = 1;
	sys_physics = main_ecs.register_system<PhysicsSystem>(physics_signature);

	Signature draw_signature = 0;
	draw_signature[COMP_SIG::POSITION] = 1;
	draw_signature[COMP_SIG::VISIBLE] = 1;
	sys_draw = main_ecs.register_system<DrawSystem>(draw_signature);

	// Set up components -- needs to be in order of COMP_SIG
	main_ecs.register_component<Position>();
	main_ecs.register_component<Translate>();
	main_ecs.register_component<Visible>(); 

	// Initial Entities
	Signature sig;
	for (int i=0; i<1000; i++) {
		Entity e = main_ecs.add_entity(sig);


		main_ecs.add_component_to_entity<Translate>(e, {rand()%100, rand()%100});

		float pos_x = (float) (rand()%800);
		float pos_y = (float) (rand()%600);
		main_ecs.add_component_to_entity<Position>(e, {pos_x, pos_y});

		Visible guy_vis;
		guy_vis.sprite = std::make_shared<sf::Sprite>(guy_tex);
		guy_vis.sprite->setPosition({pos_x, pos_y});
		guy_vis.sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));

		main_ecs.add_component_to_entity<Visible>(e, guy_vis);
		


	}

}

void MainState::update(float dt) {

	sys_physics->update(dt);

	sys_draw->update(dt);
}

void MainState::draw(sf::RenderTarget* target) {
	//sf::Texture guy_tex("../resources/graphics/guy sheet.png");
	/*sf::Sprite guy(guy_tex);*/
	/*guy.setPosition({100, 100});*/
	/*target->draw(guy);*/

	sys_draw->draw(target);
}

