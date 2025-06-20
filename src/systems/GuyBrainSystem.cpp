// System that handles making decisions for a guy. The only thing we know for
// sure is that we have a guy present. This is, like, probably against ECS ethos
// or some shit.
//
#include "components/Components.hpp"
#include <ecs/ECS.hpp>
#include <systems/GuyBrainSystem.h>

void GuyBrainSystem::update(float dt, ECS *ecs) {
  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {
    Entity ent = (Entity)*e;
    // Basically just like... subsystems ??

    /** Wandering */
    if (ecs->get_signature_for_entity(ent)[COMP_SIG::GUY_WANDERING]) {
      std::cout << "wandering " << ent << std::endl;
    }
  }
}
