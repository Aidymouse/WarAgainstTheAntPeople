
#include <engine/MainState.h>
#include <engine/GameEngine.h>
#include <memory>

GameEngine::GameEngine() {

	window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Evil Pikmin (Working title)");
	window.setFramerateLimit(144);

	//main_state = MainState();

	current_state = &main_state;
	clock.start();
	
}

void GameEngine::run() {

	while (window.isOpen()) {

		float delta_time = clock.reset().asSeconds();
		current_state->update(delta_time);

		while (const std::optional event = window.pollEvent())
		{

			current_state->handle_event(event);

			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		current_state->draw(&window);

		window.display();


	}
}
