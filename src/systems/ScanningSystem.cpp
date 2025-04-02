#include <engine/Components.hpp>
#include <iostream>
#include <systems/ScanningSystem.h>

void ScanningSystem::update(float dt, ECS *ecs) {

  ComponentArray<Scannable> scannable =
      *(component_manager->get_component_array<Scannable>());
  int num_scannable = scannable.get_num_components();
  /**/
  /**/
  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {
    Entity ent = (Entity)*e;
    // std::cout << "Drawing " << ent << std::endl;
    ScanningFor scanning_for =
        *component_manager->get_component_data<ScanningFor>(ent);

    for (int i = 0; i < num_scannable; i++) {
      Scannable s = scannable.get_data_from_idx(i);
      // std::cout << "Scannable object with type " << s.scan_value <<
      // std::endl;

      if (s.scan_value == scanning_for.sought_scan_value) {
        Entity scanned_ent = scannable.get_entity_from_idx(i);
        Position p =
            *component_manager->get_component_data<Position>(scanned_ent);

        std::cout << ent << " found scanned entity " << scanned_ent
                  << " with pos " << p.x << ", " << p.y << std::endl;

        // component_manager->get_component_array<Persuing>()->add_entity(ent, {
        // p.x, p.y });
        Persuing pe = {p.x, p.y};
        ecs->add_component_to_entity<Persuing>(ent, pe);
        // component_manager->get_component_array<ScanningFor>()->remove_entity(ent);
        break;
      }
    }
  }
}
