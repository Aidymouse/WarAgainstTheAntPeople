
#include <ctime>
#include <iostream>

#include <ProjectConfig.h>
#include <engine/Engine.h>

#include <util/Helper.h>

int main() {

  srand(time(NULL));

  std::cout << "Graphics Path: " << GRAPHICS_PATH << std::endl;

  Engine game;
  game.run();
}
