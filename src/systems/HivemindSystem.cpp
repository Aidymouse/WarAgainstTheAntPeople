#include <components/HivemindComponents.hpp>
#include <systems/HivemindBrainSystem.h>

void HivemindBrainSystem::update(float dt, ECS *ecs) {
  // Keep all the hiveminds children synced with this

  std::shared_ptr<ComponentArray<hv_Brain>> comp_brains =
      ecs->get_component_array<hv_Brain>();

  for (int h = 0; h < comp_brains->get_num_components(); h++) {

    Entity hv_entity = comp_brains->get_entity_from_idx(h);
    hv_Brain brain = comp_brains->get_data_from_idx(h);
    Position *hv_pos = ecs->get_component_for_entity<Position>(hv_entity);

    for (int ent_idx = 0; ent_idx < brain.num_entities; ent_idx++) {
      Entity attached_ent = brain.entities[ent_idx];

      Position *p = ecs->get_component_for_entity<Position>(attached_ent);
      hv_Participant *hv_info =
          ecs->get_component_for_entity<hv_Participant>(attached_ent);

      p->x = hv_pos->x - hv_info->offset.x;
      p->y = hv_pos->y - hv_info->offset.y;
    }
  }
}
