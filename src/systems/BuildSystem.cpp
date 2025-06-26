#include "components/Components.hpp"
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
}

void BuildSystem_check_buildsites(float dt, ECS *ecs, CollisionGrid *grid) {}
