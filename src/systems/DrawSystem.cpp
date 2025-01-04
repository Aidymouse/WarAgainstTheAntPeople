#include <engine/Components.hpp>
#include <iostream>
#include <systems/DrawSystem.h>

void DrawSystem::update(float dt) {
	/*for (auto e=registered_entities.begin(); e != registered_entities.end(); e++) {*/
	/*	Entity ent = (Entity) *e;*/
	/**/
	/*	Visible vis = component_manager->get_component_data<Visible>(ent);*/
	/*}*/

}

void DrawSystem::draw(sf::RenderTarget* target) {
	for (auto e=registered_entities.begin(); e != registered_entities.end(); e++) {
		Entity ent = (Entity) *e;
		//std::cout << "Drawing " << ent << std::endl;

		Visible vis = component_manager->get_component_data<Visible>(ent);
		Position pos = component_manager->get_component_data<Position>(ent);

		vis.sprite->setPosition({(float) pos.x, (float) pos.y});
		sf::Vector2f spr_pos = vis.sprite->getPosition();
		//std::cout << "Drawing " << ent << " at " << spr_pos.x << ", " << spr_pos.y << std::endl;
		target->draw(*vis.sprite);
	}
}
