#include "components/GuyComponents.hpp"
#include <cmath>
#include <components/Components.hpp>
#include <ecs/ECS.hpp>
#include <iostream>
#include <set>
#include <systems/ScanningSystem.h>
#include <util/Vec2.hpp>

void ScanningSystem::update(float dt, ECS *ecs) {

  ComponentArray<Scannable> scannable =
      *(component_manager->get_component_array<Scannable>());
  int num_scannable = scannable.get_num_components();

  std::set<Entity> ents_to_erase;

  // std::cout << ents_to_erase << std::endl;
  //
  // Eureka!
  // We need to scan for entities in rings of collision cells. That'll be way
  // faster than scanning each of them.

  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {
    Entity ent = (Entity)*e;

    ScanningFor *scanning_for =
        component_manager->get_component_data<ScanningFor>(ent);

    float shortest_dist = INFINITY;
    Entity sought_ent = -1;
    Vec2 closest_pos;
    Position *pos = component_manager->get_component_data<Position>(ent);

    for (int i = 0; i < num_scannable; i++) {
      Scannable s = scannable.get_data_from_idx(i);
      Entity scannable_ent = scannable.get_entity_from_idx(i);

      if (ent == scannable_ent)
        continue;

      bool sought = false;
      float max_scan_range = 0;
      for (int sv = 0; sv < MAX_SCAN_VALUES; sv++) {
        if (s.scan_value == scanning_for->sought_scan_values[sv]) {
          sought = true;
          max_scan_range = scanning_for->max_range[sv];
          break;
        }
      }

      // std::cout << "Scanning [" << ent << "] max range " << max_scan_range
      //           << std::endl;

      if (sought) {
        // std::cout << ent << " seeking " << s.scan_value << std::endl;
        Position p =
            *component_manager->get_component_data<Position>(scannable_ent);

        // float dist = sqrt(pow((p.x - pos->x), 2) + pow((p.y - pos->y), 2));
        float dist = pow((p.x - pos->x), 2) + pow((p.y - pos->y), 2);
        // std::cout << dist << "\n";

        if (dist < shortest_dist &&
            (max_scan_range == -1 || dist < max_scan_range * max_scan_range)) {
          sought_ent = scannable_ent;
          shortest_dist = dist;
          closest_pos.x = p.x;
          closest_pos.y = p.y;
        }
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
