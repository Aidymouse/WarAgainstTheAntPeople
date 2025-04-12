
#include <ctime>
#include <iostream>

#include <ProjectConfig.h>
#include <engine/Engine.h>

int main() {

  std::cout << "Graphics Path: " << GRAPHICS_PATH << std::endl;

  srand(time(NULL));

  Engine game;
  game.run();
}
