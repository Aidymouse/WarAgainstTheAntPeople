
#include <ctime>
#include <iostream>

#include <ProjectConfig.h>
#include <engine/Engine.h>

#include <util/Helper.h>



int main() {

	// int len = 6;
	// int arr[len] = {10, 2, 4, 6, 4, 1};
	int len = 7;
	int arr[len] = {2, 4, 6, 3, 5, 1, 5};
//arr[7] = 42;

 int start = 0;
 int end = len-1;

	Helper::quicksort(arr, start, end);	
	
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
