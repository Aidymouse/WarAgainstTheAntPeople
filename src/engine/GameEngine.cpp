
#include <engine/MainState.h>
#include <engine/GameEngine.h>
#include <memory>

GameEngine::GameEngine() {

	window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Evil Pikmin (Working title)");
	window.setFramerateLimit(144);

	//main_state = MainState();

	current_state = &main_state;
	
}

void GameEngine::run() {

	while (window.isOpen()) {

		while (const std::optional event = window.pollEvent())
		{
		    if (event->is<sf::Event::Closed>())
		    {
			window.close();
		    }
		}

		current_state->update(0.016);
		current_state->draw(&window);

		window.display();


	}
}
