
#include <ctime>
#include <iostream>

#include <engine/Engine.h>
#include <ProjectConfig.h>


int main() {

	std::cout << "Graphics Path: " << GRAPHICS_PATH << std::endl;

	srand(time(NULL));

	Engine game;
	game.run();


}
