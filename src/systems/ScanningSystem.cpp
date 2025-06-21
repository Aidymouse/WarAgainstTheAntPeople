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

    // std::cout << "Scanning " << ent << " ("
    //           << ecs->get_signature_for_entity(ent) << ")" << std::endl;
    ScanningFor *scanning_for =
        component_manager->get_component_data<ScanningFor>(ent);

    float shortest_dist = INFINITY;
    Vec2 closest_pos;
    Position *pos = component_manager->get_component_data<Position>(ent);

    for (int i = 0; i < num_scannable; i++) {
      Scannable s = scannable.get_data_from_idx(i);

      if (s.scan_value == scanning_for->sought_scan_value) {
        Entity scanned_ent = scannable.get_entity_from_idx(i);
        Position p =
            *component_manager->get_component_data<Position>(scanned_ent);

        // float dist = sqrt(pow((p.x - pos->x), 2) + pow((p.y - pos->y), 2));
        float dist = pow((p.x - pos->x), 2) + pow((p.y - pos->y), 2);
        // std::cout << dist << "\n";

        if (dist < shortest_dist) {
          shortest_dist = dist;
          closest_pos.x = p.x;
          closest_pos.y = p.y;
        }

        // std::cout << ent << " found scanned entity " << scanned_ent
        //           << " with pos " << p.x << ", " << p.y << std::endl;

        // component_manager->get_component_array<Persuing>()->add_entity(ent, {
        // p.x, p.y });
        // Persuing pe = {p.x, p.y};
        // ents_to_erase.insert(ent);
        // ents_to_erase++ ;

        // ecs->remove_component_from_entity<ScanningFor>(ent);
        //  component_manager->get_component_array<ScanningFor>()->remove_entity(ent);
        // break;
      }
    }

    if (shortest_dist < 20) {
      ents_to_erase.insert(ent);
      Transform *trans = component_manager->get_component_data<Transform>(ent);
      trans->vel_x = 0;
      trans->vel_y = 0;
    } else {
      Vec2 vecPos = Vec2(pos->x, pos->y);
      Vec2 desiredPos = Vec2(closest_pos.x, closest_pos.y);
      Vec2 diff = vecPos - desiredPos;
      Vec2 dir = diff.normalized();

      Vec2 newPos = vecPos + dir;
      // ecs->add_component_to_entity<Persuing>(ent, pe);

      Transform *trans = component_manager->get_component_data<Transform>(ent);
      trans->vel_x = -dir.x * 50;
      trans->vel_y = -dir.y * 50;
    }
  }

  // Clean up, remove ents
  for (auto e = ents_to_erase.begin(); e != ents_to_erase.end(); e++) {
    Entity ent = *e;
    ecs->remove_component_from_entity<ScanningFor>(ent);
  }
}
