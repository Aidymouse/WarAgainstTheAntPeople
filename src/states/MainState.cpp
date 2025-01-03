#include <SFML/Graphics/Texture.hpp>
#include <ecs/ECS.hpp>
#include <sstream>
#include <string>
#include <systems/PhysicsSystem.h>
#include <systems/DrawSystem.h>
#include <ecs/Components.hpp>

#include <states/MainState.h>
#include <ProjectConfig.h>


std::string G = std::string(GRAPHICS_PATH);
const sf::Texture guy_tex(G.append("guy sheet.png"));

MainState::MainState() {
	ECS main_ecs;

	// Set up Systems
	Signature physics_signature = 0;
	physics_signature[0] = 1;
	physics_signature[1] = 1;
	sys_physics = main_ecs.register_system<PhysicsSystem>(physics_signature);

	Signature draw_signature = 0;
	draw_signature[2] = 1;
	sys_draw = main_ecs.register_system<DrawSystem>(draw_signature);

	// Set up components
	main_ecs.register_component<Position>();
	main_ecs.register_component<Translate>();
	main_ecs.register_component<Visible>(); 

	// Initial Entities
	Signature sig;
	for (int i=0; i<10; i++) {
		Entity e = main_ecs.add_entity(sig);


		if (rand()%2 == 0) {
			main_ecs.add_component_to_entity<Position>(e, {rand()%800, rand()%600});
		}

		if (rand()%2 == 0) {
			main_ecs.add_component_to_entity<Translate>(e, {rand()%800, rand()%600});
		}

		if (rand()%2 == 0) {
			Visible guy_vis;
			guy_vis.sprite = std::make_shared<sf::Sprite>(guy_tex);
			guy_vis.sprite->setPosition({(float) (rand()%800), (float) (rand()%600)});
			guy_vis.sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));

			main_ecs.add_component_to_entity<Visible>(e, guy_vis);
		} 
		


	}

}

void MainState::update(float dt) {
	//sys_physics->update(dt);
}

void MainState::draw(sf::RenderTarget* target) {
	//sf::Texture guy_tex("../resources/graphics/guy sheet.png");
	/*sf::Sprite guy(guy_tex);*/
	/*guy.setPosition({100, 100});*/
	/*target->draw(guy);*/

	sys_draw->draw(target);
}

