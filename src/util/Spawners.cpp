#include <data/Attrs.hpp>
#include <data/TextureStore.hpp>

#include <state_machines/GuySM.h>
#include <util/Spawners.h>

#include <components/GuyComponents.hpp>
#include <ecs/ECS.hpp>
#include <engine/CollisionGrid.h>

#include "anim/GuyAnim.hpp"
#include "anim/NotMovingAnim.hpp"
#include "components/Collisions.hpp"
#include "components/Components.hpp"
#include "engine/Collisions.h"
#include "util/Random.h"

TextureStore &spawners_texture_store = TextureStore::getInstance();

void Spawners::add_guy(ECS *ecs, CollisionGrid *grid) {

	Visible v = { spawners_texture_store.get("guy_sheet"), GuyAnim.NORM, 0, {0, 0} };
	float x = (float)(Random::rand_range(0, WINDOW_WIDTH));
	float y = (float)(Random::rand_range(0, WINDOW_HEIGHT));
	Position p = {x, y, 0};
	// Position p = {WINDOW_WIDTH / 2, 400, 0};
	Collider c = {CollisionShapeType::CIRCLE, {x, y, 6}, CollisionIdentifier::CI_GUY};
	Entity g = ecs->add_entity();
	ecs->add_component_to_entity<Visible>(g, v);
	ecs->add_component_to_entity<Position>(g, p);
	ecs->add_component_to_entity<Transform>(g, {0, 0, 0});
	ecs->add_component_to_entity<Collider>(g, c);
	ecs->add_component_to_entity<GuyBrain>(g, {});
	ecs->add_component_to_entity<HandsFree>(g, {});

	// if (rand() % 100 < 10) {
	ecs->add_component_to_entity<ScanningFor>( g, {
		{SCAN_VALUES::SV_CARRIED_SCRAP, SCAN_VALUES::SV_SCRAP_METAL, -1, -1},
		{GuyAttrs.scan_range, GuyAttrs.scan_range, 0, 0}
	});
	// } else {
	//	 g_Wandering *w = GuySM::enter_wandering(g, ecs);
	// }
	// g_Wandering *w2 = GuySM::enter_wandering(g, ecs);

	grid->update_entity(g, p, c);

	// std::cout << "Added guy [" << g << "] at " << x << ", " << y << std::endl;
}

void Spawners::add_scrap(ECS *ecs, CollisionGrid *grid) {
	Visible v = {spawners_texture_store.get("scrap_sheet"), NotMovingAnim.SCRAP};
	float x = (float)(Random::rand_range(0, WINDOW_WIDTH));
	float y = (float)(Random::rand_range(0, WINDOW_HEIGHT));
	Position p = {x, y};
	Carryable carry_data = {0, 0, 5, 125, 51}; // TODO should come from somewhere dynamic

	Entity s = ecs->add_entity();

	std::cout << "Added scrap " << s << std::endl;

	Collider c = {
		CollisionShapeType::CIRCLE,
		{x, y, 8},
		CollisionIdentifier::CI_RESOURCE
	};
	ecs->add_component_to_entity<Resource>(s, {ResourceTypes::RT_SCRAP_METAL, 1});
	ecs->add_component_to_entity<Visible>(s, v);
	ecs->add_component_to_entity<Position>(s, p);
	ecs->add_component_to_entity<Scannable>(s, {SCAN_VALUES::SV_SCRAP_METAL});
	ecs->add_component_to_entity<Carryable>(s, carry_data);
	ecs->add_component_to_entity<Collider>(s, c);

	grid->update_entity(s, p, c);
}
