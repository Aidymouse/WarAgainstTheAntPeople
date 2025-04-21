
#include <ctime>
#include <iostream>

#include <ProjectConfig.h>
#include <engine/Engine.h>

#include <util/Helper.h>


void cout_arr(int* a, int l) {
	for (int i=0; i<l; i++) {
		std::cout << a[i] << ", ";
	}
}

int main() {

  	srand(time(NULL));

	// int len = 6;
	// int arr[len] = {10, 2, 4, 6, 4, 1};
	// int len = 7;
	// int arr[len] = {2, 4, 6, 3, 5, 1, 5};
	int len = 99;
	int arr[len] = {0};
	for (int i=0; i<10000; i++) {
		for (int k=0; k<len; k++) {
			arr[k] = rand() % 60 - 30;
		}
		std::cout << std::endl << " === Sorting ";
		cout_arr(arr, len);
		std::cout << std::endl;

		bool partition_validated = Helper::quicksort(arr, 0, len-1);	
		// std::cout << "QUICKSORTED: ";
		// cout_arr(arr, len);
		if (!partition_validated) {
			std::cout << "PARTITION FAILED" << std::endl;
			break;
		}
		//
		bool validated = true;
		for (int k=1; k<len; k++) {
			if (arr[k-1] > arr[k]) {
				validated=false;
				break;
			}

		}


		std::cout << " - "; 
		if (validated) {
			std::cout << "Pass" << std::endl;
		} else {
			std::cout << "Fail" << std::endl;
			break;
		}
	}

	



  // std::cout << "Graphics Path: " << GRAPHICS_PATH << std::endl;
  //
  //
  // Engine game;
  // game.run();
}
