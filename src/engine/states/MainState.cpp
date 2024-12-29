#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <iostream>

#include <data/TextureBank.h>
#include <data/EntityAttributes.h>

#include <engine/MainState.h>
#include <engine/MenuState.h>
#include <engine/Collisions.h>

#include <entity/Entity.h>
#include <entity/Guy.h>
#include <entity/Mallet.h>

MainState::MainState() : GameState::GameState() {

	//const sf::Texture testTex("../resources/graphics/guy sheet.png");


	Guy g;
	g.animation_frame = frames_Guy::NORM1;

	for (int i=0; i<2500; i++) {

		g.x = rand() % 800;
		g.y = rand() % 600;
		//std::cout << g.x << std::endl;
		main_grid.insert_guy(g);
	}

}


void MainState::update(float dt) {
	// Tools
	
	// Other entities
	
	// Guys + Check for Collisions + update some stuff
	/*for (int cell_idx = 0; cell_idx<main_grid.get_cell_count(); cell_idx++) {*/
	/*	CollisionCell* cell = main_grid.get_cell(cell_idx);*/
	/*	for (int guy_idx = 0; guy_idx < cell->get_guy_count(); guy_idx++) {*/
	/*		Guy *g = cell->get_guy(guy_idx);*/
	/**/
	/*	}*/
	/*}*/
	
	// Apply updates to entities
}

void MainState::load() {}

void MainState::handle_event(const std::optional<sf::Event> event) {

	// Mouse Pressed
	if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
		//std::cout << "Mouse Pressed: " << mouseButtonPressed->position.x << ", " << mouseButtonPressed->position.y << std::endl;
		//

		if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
			if (grabbed_tool != NULL) {

			} else {
				CollisionCircle mouse_collision_shape = {
					CollisionShapeType::CIRCLE,
					mouseButtonPressed->position.x,
					mouseButtonPressed->position.y,
					1
				};


				if (Collisions::circle_circle(mallet.get_collision_shape().circle, mouse_collision_shape)) {
					grabbed_tool = &mallet;
				}
			}
		} else if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
			if (grabbed_tool != NULL) {
				grabbed_tool = NULL;
			}
		}


	}

	if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
		if (grabbed_tool != NULL) {
			grabbed_tool->handle_mousemove(mouseMoved->position);
		}
	}

}

void MainState::draw(sf::RenderTarget* target) {

	target->clear(sf::Color::White);

	// Tools
	target->draw(mallet.get_sprite());
	/*sf::CircleShape mallet_circle(16);*/
	/*mallet_circle.setPosition({100, 100});*/
	/*mallet_circle.setOrigin({16, 16});*/
	/*mallet_circle.setFillColor(sf::Color::Red);*/
	/*target->draw(mallet_circle);*/
	
	// Guys
	int cell_count = main_grid.get_cell_count();
	sf::Sprite guy_sprite(TextureBank::guy);
	guy_sprite.setOrigin({EntityAttributes::Guy.origin_x, EntityAttributes::Guy.origin_y });

	for (int cell_idx = 0; cell_idx<cell_count; cell_idx++) {
		CollisionCell* cell = main_grid.get_cell(cell_idx);

		int guy_count = cell->get_guy_count();
		sf::IntRect guy_rect({0, 0}, {16, 16});

		for (int guy_idx=0; guy_idx<guy_count; guy_idx++) {
			Guy* guy = cell->get_guy(guy_idx);
			//std::cout << "Guy " << guy_idx << ": " << guy->x << ", " << guy->y << std::endl;
			guy_sprite.setTextureRect({{0, 0}, {16, 16}});
			guy_sprite.setPosition({(float) guy->x, (float) guy->y});
			target->draw(guy_sprite);
		}
		
	}
}
