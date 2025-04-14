
#include <systems/FollowsMouseSystem.h>

void FollowsMouseSystem::update(float dt, ECS *ecs, CollisionGrid *grid) {

  float mX = -1;
  float mY = -1;

  SDL_GetMouseState(&mX, &mY);

  // std::cout << mX << ", " << mY << std::endl;

  for (auto e = registered_entities.begin(); e != registered_entities.end();
       e++) {
    Entity ent = (Entity)*e;
    Position *pos = component_manager->get_component_data<Position>(ent);

    pos->x = mX;
    pos->y = mY;

    if (ecs->get_signature_for_entity(ent)[COMP_SIG::COLLIDER] == 1) {
      Collider *c = component_manager->get_component_data<Collider>(ent);
      // std::cout << "Collider for " << ent << ", " << c << std::endl;

      Collisions::update_collider_position(c, pos->x, pos->y);

      grid->update_entity(ent, *pos, *c);
    }

  }
};
