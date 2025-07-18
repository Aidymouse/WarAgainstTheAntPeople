#include "components/GuyComponents.hpp"
#include <cmath>
#include <components/Components.hpp>
#include <ecs/ECS.hpp>
#include <iostream>
#include <set>
#include <systems/ScanningSystem.h>
#include <util/Vec2.hpp>
#include <SDL3/SDL.h>
#include <util/DrawFns.h>

/** When scanning for an object, an entity will target the closest object with the highest priority 
 * (the order of scan values in the ScanningFor component is priority order) 
 * */
void ScanningSystem::update(float dt, ECS *ecs) {

	ComponentArray<Scannable> comp_scannable = *(component_manager->get_component_array<Scannable>());
	int num_scannable = comp_scannable.get_num_components();

	std::set<Entity> ents_to_erase;

	// Eureka!
	// TODO: We need to scan for entities in rings of collision cells. That'll be way faster than scanning each of them.

	/** Scan for nearby things with priority and add persuing component if we find something */
 	for (auto e = registered_entities.begin(); e != registered_entities.end(); e++) {
		Entity ent = (Entity)*e;

		/*
		std::cout << "Scanning System Processing for [" << ent << "]" << std::endl;
		ecs->debug_cout_entity_state(ent);
		*/

		ScanningFor *scanning_for = component_manager->get_component_data<ScanningFor>(ent);

		float dist_to_target = INFINITY;
		Entity sought_ent = -1;
		Vec2 target_pos;
		Position *pos = component_manager->get_component_data<Position>(ent);
		SCAN_VALUES value_of_target_ent;
		int priority_of_sought = MAX_SCAN_VALUES+1; // Only updated when one is found in range

		for (int i = 0; i < num_scannable; i++) {
			Scannable s = comp_scannable.get_data_from_idx(i);
			Entity scannable_ent = comp_scannable.get_entity_from_idx(i);

			if (ent == scannable_ent) { continue; }

			// Get priority of this entity
			float cur_scanning_priority = MAX_SCAN_VALUES+1;
			float max_scan_range = INFINITY;

			for (int sv = 0; sv < MAX_SCAN_VALUES; sv++) {
				if (scanning_for->sought_scan_values[sv] == -1) { break; }
				if (s.scan_value == scanning_for->sought_scan_values[sv]) {
					cur_scanning_priority = sv;
					max_scan_range = scanning_for->max_range[sv];
					break;
				}
			}

			if (max_scan_range == INFINITY) { continue; } // We are not looking for this kind of scannable

			// Test if sought is in range
			Position p = *component_manager->get_component_data<Position>(scannable_ent);
			float dist = pow((p.x - pos->x), 2) + pow((p.y - pos->y), 2);

			// Squaring max scan range means i dont need to square root tee hee
			if (max_scan_range != -1 && dist > max_scan_range * max_scan_range) { continue; } // Out of range!

			if (cur_scanning_priority > priority_of_sought)	{
				continue;
			} else if (cur_scanning_priority < priority_of_sought) {
				// Passthrough, we always want higher priority (earlier index = higher)
			} else if (cur_scanning_priority == priority_of_sought) {
				// Take shortest dist
				if (dist > dist_to_target) { continue; }
			}

			sought_ent = scannable_ent;
			dist_to_target = dist;
			target_pos.x = p.x;
			target_pos.y = p.y;
			priority_of_sought = cur_scanning_priority;
			//std::cout << "[" << ent << "] found " << s.scan_value << " with Shortest Dist " << shortest_dist << std::endl;
			//ecs->debug_cout_entity_state(ent);
		}

		if (sought_ent != -1) {
			if (!ecs->entity_has_component<Persuing>(ent)) {
				ecs->add_component_to_entity<Persuing>(ent, {0, 0});
				ecs->remove_component_from_entity<g_Wandering>(ent);
			}

			//std::cout << "[" << ent << "] Seeking towards [" << sought_ent << "] (" << ecs->get_component_for_entity<Scannable>(sought_ent)->scan_value << ")" << std::endl;

			Persuing *per = ecs->get_component_for_entity<Persuing>(ent);
			per->desiredX = target_pos.x;
			per->desiredY = target_pos.y;
		} else {
			ecs->remove_component_from_entity<Persuing>(ent);

			//std::cout << "[" << ent << "] didnt find anything to scan (closest was " << dist_to_target << " away)" << std::endl;
			//ecs->debug_cout_entity_state(ent);
		}
	}

	// Clean up, remove ents
	for (auto e = ents_to_erase.begin(); e != ents_to_erase.end(); e++) {
		Entity ent = *e;
		ecs->remove_component_from_entity<ScanningFor>(ent);
	}


	/** Process Pursuit */
	std::shared_ptr<ComponentArray<Persuing>> comp_persuing = ecs->get_component_array<Persuing>();

	for (int i = 0; i < comp_persuing->get_num_components(); i++) {
		Entity persuing_ent = comp_persuing->get_entity_from_idx(i);

		// std::cout << "[" << i << "]" << std::endl;
		Position *pos = ecs->get_component_for_entity<Position>(persuing_ent);
		Persuing pur = comp_persuing->get_data_from_idx(i);

		Vec2 vecPos = Vec2(pos->x, pos->y);
		Vec2 desiredPos = Vec2(pur.desiredX, pur.desiredY);
		Vec2 diff = vecPos - desiredPos;
		Vec2 dir = diff.normalized();

		Vec2 newPos = vecPos + dir;
		// ecs->add_component_to_entity<Persuing>(ent, pe);

		int pursuit_speed = 50;

		// If i'm being carried, total effort changes the speed of pursuit

		Transform *trans = component_manager->get_component_data<Transform>(persuing_ent);
		trans->vel_x = -dir.x * pursuit_speed;
		trans->vel_y = -dir.y * pursuit_speed;

		if (!ecs->entity_has_component<GuyBrain>(persuing_ent)) {
			trans->vel_x = -dir.x * pursuit_speed;
			trans->vel_y = -dir.y * pursuit_speed;
		}

		// std::cout << "Trans [" << ent << "]" << std::endl;
	}

}

void ScanningSystem::debug_draw(SDL_Renderer *renderer, ECS *ecs) {

	std::shared_ptr<ComponentArray<ScanningFor>> comp_scanningfor = ecs->get_component_array<ScanningFor>();
	for (int i = 0; i < comp_scanningfor->get_num_components(); i++) {
		Entity scanningfor_ent = comp_scanningfor->get_entity_from_idx(i);

		//if (ecs->entity_has_component<Persuing>(scanningfor_ent)) { continue; }

		ScanningFor sfor = comp_scanningfor->get_data_from_idx(i);
		Position pos = *ecs->get_component_for_entity<Position>(scanningfor_ent);
		for (int j=0; j<MAX_SCAN_VALUES; j++) {
			if (sfor.max_range[j] == -1) { break; }
  			DrawFns::RenderCircle(renderer, pos.x, pos.y, sfor.max_range[j]);
		}

	}

	std::shared_ptr<ComponentArray<Persuing>> comp_persuing = ecs->get_component_array<Persuing>();

	for (int i = 0; i < comp_persuing->get_num_components(); i++) {
		Entity persuing_ent = comp_persuing->get_entity_from_idx(i);
		Persuing per = comp_persuing->get_data_from_idx(i);

		Position pos = *ecs->get_component_for_entity<Position>(persuing_ent);

		SDL_RenderLine(renderer, pos.x, pos.y, per.desiredX, per.desiredY);
	}

}
