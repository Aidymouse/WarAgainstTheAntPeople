
#include <systems/CarrySystem.h>

void CarrySystem::update(float dt, ECS *ecs) {
  std::shared_ptr<ComponentArray<Carryable>> comp_carryable =
      ecs->get_component_array<Carryable>();
}
