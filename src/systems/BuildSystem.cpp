#include "anim/BuildsiteAnim.hpp"
#include "components/Components.hpp"
#include <anim/BuildsiteAnim.hpp>
#include <systems/BuildSystem.h>

void BuildSystem_check_resources(float dt, ECS *ecs, CollisionGrid *grid);
void BuildSystem_check_buildsites(float dt, ECS *ecs, CollisionGrid *grid);

/** Looks at build sites and resources and determines if a buildsite should be
 * created or added to */
void BuildSystem::update(float dt, ECS *ecs, CollisionGrid *grid) {
  BuildSystem_check_resources(dt, ecs, grid);
}

void BuildSystem_check_resources(float dt, ECS *ecs, CollisionGrid *grid) {
  std::shared_ptr<ComponentArray<Resource>> comp_resource =
      ecs->get_component_array<Resource>();

  for (int r = 0; r < comp_resource->get_num_components(); r++) {
    Entity resource_id = comp_resource->get_entity_from_idx(r);

    std::cout << "Checking build system for [" << resource_id << "]"
              << std::endl;
    // If two resources are touching and at least one of them is being carried
    // then they should transform into a buildsite
    Collider *resource_c = ecs->get_component_for_entity<Collider>(resource_id);

    bool is_carried = false;
    if (ecs->entity_has_component<Carryable>(resource_id)) {
      Carryable *resource_e =
          ecs->get_component_for_entity<Carryable>(resource_id);

      if (resource_e->carriers_count > 0) {
        is_carried = true;
      }
    }

    std::set<Entity> collided_resources =
        grid->get_collisions(*resource_c, ecs);

    for (auto resource_e = collided_resources.begin();
         resource_e != collided_resources.end(); resource_e++) {
      Entity collided_resource_ent = (Entity)*resource_e;
      if (!ecs->entity_has_component<Resource>(collided_resource_ent))
        continue;

      if (collided_resource_ent == resource_id)
        continue;

      if ((ecs->entity_has_component<Carryable>(collided_resource_ent) &&
           ecs->get_component_for_entity<Carryable>(collided_resource_ent)
                   ->carriers_count > 0) ||
          is_carried) {
        // Turn me into buildsite and remove other
        ecs->remove_entity(collided_resource_ent);

        ecs->remove_component_from_entity<Resource>(resource_id);
        ecs->remove_component_from_entity<Carryable>(resource_id);

        Buildable b = {1,
                       4,
                       {
                           bs_TowerAnim.BUILD1,
                           bs_TowerAnim.BUILD2,
                           bs_TowerAnim.BUILD3,
                           bs_TowerAnim.BUILD4,
                       },
                       {5, 5, 5, 5},
                       0};

        ecs->add_component_to_entity<Buildable>(resource_id, b);
      }
    }
  }
}

void BuildSystem_check_buildsites(float dt, ECS *ecs, CollisionGrid *grid) {}
