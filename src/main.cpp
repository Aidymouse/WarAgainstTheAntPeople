
#include <ctime>
#include <iostream>

#include <ProjectConfig.h>
#include <engine/Engine.h>
#include <util/Random.h>

#include <util/Helper.h>

int main() {

  srand(time(NULL));

  std::cout << "Graphics Path: " << GRAPHICS_PATH << std::endl;

  // int angle[8] = {0, 45, 90, 135, 180, 225, 270, 315};
  //
  // Vec2 up(0, -1);
  // for (int i = 0; i < 8; i++) {
  //   up.face_angle(angle[i]);
  //   float a = up.get_angle_facing();
  //   std::cout << "Up [" << i << "]: " << up << ", " << a << std::endl;
  // }

  Engine game;
  game.run();
}
