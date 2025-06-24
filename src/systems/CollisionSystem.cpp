#include "components/Collisions.hpp"
#include "components/Components.hpp"
#include <engine/CollisionGrid.h>
#include <systems/CollisionSystem.h>

void CollisionSystem::update(float dt, ECS *ecs, CollisionGrid *grid) {

  const bool debug = false;

  std::shared_ptr comp_colliders = ecs->get_component_array<Collider>();

  for (int i = 0; i < comp_colliders->get_num_components(); i++) {
    Collider c = comp_colliders->get_data_from_idx(i);
    if (c.collision_data.type == CollisionType::NO_OP)
      continue; // TODO optimization with passive/active colliders here
    std::set<Entity> collides_with = grid->get_collisions(c, ecs);

    // TODO: only allow one collision of the same type from the same entity
    for (auto e = collides_with.begin(); e != collides_with.end(); e++) {
      Collided *cd;
      Entity collided_ent = (Entity)*e;

      if (ecs->entity_has_component<Collided>(collided_ent)) {
        cd = ecs->get_component_for_entity<Collided>(collided_ent);
      } else {
        Collided default_cd = {{}, 0};
        ecs->add_component_to_entity<Collided>(collided_ent, default_cd);
        cd = ecs->get_component_for_entity<Collided>(collided_ent);
      }
      // TODO one day we should filter collisions here, since you can only store
      // 4 they might as well be four valid collisions. Plus saves filtering
      // logic later
      if (cd->num_collisions >= MAX_COLLISIONS_PER_ENTITY) {
        if (debug) {
          std::cout << "Entity (" << collided_ent << ") already has "
                    << MAX_COLLISIONS_PER_ENTITY << " collisions" << std::endl;
        }
      } else {
        if (debug) {
          std::cout << "Entity (" << collided_ent << ") collided with ("
                    << comp_colliders->get_entity_from_idx(i) << ")"
                    << std::endl;
        }
        int nc = cd->num_collisions;
        cd->collisions[nc] = c.collision_data;
        cd->num_collisions += 1;
      }
    }
  }
}

void CollisionSystem::strip_collided(float dt, ECS *ecs) {

  std::shared_ptr<ComponentArray<Collided>> comp_collided =
      ecs->get_component_array<Collided>();

  for (int i = 0; i < comp_collided->get_num_components(); i++) {
    Collided *c = comp_collided->get_editable_data_from_idx(i);
    c->num_collisions = 0;
  }
}
