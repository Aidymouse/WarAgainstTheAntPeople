#include "components/GuyComponents.hpp"
#include <cmath>
#include <components/Components.hpp>
#include <ecs/ECS.hpp>
#include <iostream>
#include <set>
#include <systems/ScanningSystem.h>
#include <util/Vec2.hpp>

/** When scanning for an object, an entity will target the closest object with the highest priority 
 * (the order of scan values in the ScanningFor component is priority order) 
 * */
void ScanningSystem::update(float dt, ECS *ecs) {

	ComponentArray<Scannable> comp_scannable = *(component_manager->get_component_array<Scannable>());
	int num_scannable = comp_scannable.get_num_components();

	std::set<Entity> ents_to_erase;

  // Eureka!
  // We need to scan for entities in rings of collision cells. That'll be way
  // faster than scanning each of them.

 	for (auto e = registered_entities.begin(); e != registered_entities.end(); e++) {
    	Entity ent = (Entity)*e;

		/*
		std::cout << "Scanning System Processing for [" << ent << "]" << std::endl;
		ecs->debug_cout_entity_state(ent);
		*/

    ScanningFor *scanning_for =
        component_manager->get_component_data<ScanningFor>(ent);

    float shortest_dist = INFINITY;
    Entity sought_ent = -1;
    Vec2 closest_pos;
    Position *pos = component_manager->get_component_data<Position>(ent);

	int earliest_scan_value_found = MAX_SCAN_VALUES+1; // Very simple priority system

	for (int i = 0; i < num_scannable; i++) {
	Scannable s = comp_scannable.get_data_from_idx(i);
	Entity scannable_ent = comp_scannable.get_entity_from_idx(i);

      if (ent == scannable_ent)
        continue;

	bool sought = false;
	float max_scan_range = 0;

	for (int sv = 0; sv < MAX_SCAN_VALUES; sv++) {
		if (s.scan_value == scanning_for->sought_scan_values[sv] && sv <= earliest_scan_value_found) {
			sought = true;
			earliest_scan_value_found = sv;
			max_scan_range = scanning_for->max_range[sv];
			break;
		}
	}

	if (!sought) continue;

	Position p = *component_manager->get_component_data<Position>(scannable_ent);
	float dist = pow((p.x - pos->x), 2) + pow((p.y - pos->y), 2);

	// Squaring max scan range means i dont need to square root tee hee
	if (dist < shortest_dist && (max_scan_range == -1 || dist < max_scan_range * max_scan_range)) {
		sought_ent = scannable_ent;
		shortest_dist = dist;
		closest_pos.x = p.x;
		closest_pos.y = p.y;
	}
	// std::cout << "[" << ent << "] Shortest Dist " << shortest_dist;
    }

    if (shortest_dist != INFINITY) {
      if (!ecs->entity_has_component<Persuing>(ent)) {
        ecs->add_component_to_entity<Persuing>(ent, {0, 0});
        ecs->remove_component_from_entity<g_Wandering>(ent);
      }

      // std::cout << "[" << ent << "] Seeking towards [" << sought_ent << "]"
      // << std::endl;

      Persuing *per = ecs->get_component_for_entity<Persuing>(ent);
      per->desiredX = closest_pos.x;
      per->desiredY = closest_pos.y;
    } else {
      ecs->remove_component_from_entity<Persuing>(ent);
    }
  }

  std::shared_ptr<ComponentArray<Persuing>> comp_persuing =
      ecs->get_component_array<Persuing>();

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

    Transform *trans =
        component_manager->get_component_data<Transform>(persuing_ent);
    trans->vel_x = -dir.x * 50;
    trans->vel_y = -dir.y * 50;

    if (!ecs->entity_has_component<GuyBrain>(persuing_ent)) {
      trans->vel_x = -dir.x * 50;
      trans->vel_y = -dir.y * 50;
    }

    // std::cout << "Trans [" << ent << "]" << std::endl;
  }

  // Clean up, remove ents
  for (auto e = ents_to_erase.begin(); e != ents_to_erase.end(); e++) {
    Entity ent = *e;
    ecs->remove_component_from_entity<ScanningFor>(ent);
  }
}
