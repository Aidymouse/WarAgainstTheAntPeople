#include <string>

#include <states/MainState.h>
#include <SFML/Graphics/Texture.hpp>

#include <ecs/ECS.hpp>
#include <systems/DrawSystem.h>
#include <systems/ToolMouse.h>

#include <engine/Components.hpp>
#include <data/TextureStore.hpp>

#include <ProjectConfig.h>

void create_guy(ECS* ecs) {
	Entity e = ecs->add_entity();

	float pos_x = (float) (rand()%800);
	float pos_y = (float) (rand()%600);
	ecs->add_component_to_entity<Position>(e, {pos_x, pos_y});

	Visible guy_vis;
	guy_vis.sprite = std::make_shared<sf::Sprite>(TextureStore::GUY);
	guy_vis.sprite->setPosition({pos_x, pos_y});
	guy_vis.sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));

	ecs->add_component_to_entity<Visible>(e, guy_vis);
	ecs->add_component_to_entity<ColliderHandler_mallet>(e, {});
};

MainState::MainState() {
	ECS main_ecs;

	// Set up Systems

	Signature draw_signature = 0;
	draw_signature[COMP_SIG::POSITION] = 1;
	draw_signature[COMP_SIG::VISIBLE] = 1;
	sys_draw = main_ecs.register_system<DrawSystem>(draw_signature);

	Signature toolmouse_signature = 0;
	toolmouse_signature[COMP_SIG::COLLIDER] = 1;
	toolmouse_signature[COMP_SIG::CLICKABLE] = 1;
	sys_toolmouse = main_ecs.register_system<ToolMouse>(toolmouse_signature);

	// Set up components -- needs to be in order of COMP_SIG
	main_ecs.register_component<Position>();
	main_ecs.register_component<Visible>(); 
	main_ecs.register_component<Tool>(); 
	main_ecs.register_component<Clickable>(); 

	main_ecs.register_component<Collider>(); 
	main_ecs.register_component<ColliderHandler_mallet>(); 

	/** Initial Entities */
	
	// Tools
	Entity mallet_id = main_ecs.add_entity();
	main_ecs.add_component_to_entity<Tool>(mallet_id, {0});
	Visible mallet_visible;
	float mallet_x = rand()%800;
	float mallet_y = rand()%800;
	mallet_visible.sprite = std::make_shared<sf::Sprite>(TextureStore::MALLET);
	mallet_visible.sprite->setPosition({mallet_x, mallet_y});
	mallet_visible.sprite->setTextureRect(sf::IntRect({0, 0}, {32, 32}));
	mallet_visible.sprite->setOrigin({16, 16});
	main_ecs.add_component_to_entity<Visible>(mallet_id, mallet_visible);
	main_ecs.add_component_to_entity<Position>(mallet_id, {mallet_x, mallet_y});
	main_ecs.add_component_to_entity<Collider>(mallet_id, { CollisionShapeType::CIRCLE, {mallet_x, mallet_y, 16}, 0 });
	main_ecs.add_component_to_entity<Clickable>(mallet_id, {});

	
	// Guys
	for (int i=0; i<100; i++) {
		create_guy(&main_ecs);
	}

}

void MainState::handle_click(const sf::Event::MouseButtonPressed* evt) {
	sys_toolmouse->handle_click(evt);
}

void MainState::handle_mousemove(const sf::Event::MouseMoved* evt) {
	sys_toolmouse->handle_mousemove(evt);
}

void MainState::update(float dt) {


	sys_draw->update(dt);
}

void MainState::draw(sf::RenderTarget* target) {
	//sf::Texture guy_tex("../resources/graphics/guy sheet.png");
	/*sf::Sprite guy(guy_tex);*/
	/*guy.setPosition({100, 100});*/
	/*target->draw(guy);*/

	sys_draw->draw(target);
	sys_toolmouse->draw(target);
}

