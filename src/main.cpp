
#include <ctime>
#include <systems/PhysicsSystem.h>
#include <iostream>

#include <ecs/ComponentArray.hpp>
#include <ecs/ECS.hpp>

#include <engine/Components.hpp>
#include <engine/Engine.h>
#include <ProjectConfig.h>


int main() {

	std::cout << "Graphics Path: " << GRAPHICS_PATH << std::endl;

	srand(time(NULL));

	Engine game;
	game.run();


}
