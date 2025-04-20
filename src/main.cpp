
#include <ctime>
#include <iostream>

#include <ProjectConfig.h>
#include <engine/Engine.h>

#include <util/Helper.h>


int main() {

	int len = 9;
 int arr[len] = {2, 5, 5, 5, 5, 3, 4, 1, 6};

  Helper::quicksort(arr, 0, len-1);

  for (int i=0; i<len; i++) {
   std::cout << arr[i] << ", ";
  }
  // std::cout << "Graphics Path: " << GRAPHICS_PATH << std::endl;
  //
  // srand(time(NULL));
  //
  // Engine game;
  // game.run();
}
