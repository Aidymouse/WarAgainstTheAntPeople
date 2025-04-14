
#include <systems/FollowsMouseSystem.h>

void FollowsMouseSystem::update(float dt) {

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
  }
};
