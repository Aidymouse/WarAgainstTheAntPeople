#include <engine/Engine.h>
#include <states/MainState.h>

Engine::Engine() {
	window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Evil Pikmin (a ha ha ha)");
	clock.start();

	state_manager.set_state(std::make_shared<MainState>());
}

void Engine::run() {
	
	while (window.isOpen()) {

		while (const std::optional event = window.pollEvent())
		{
		    if (event->is<sf::Event::Closed>())
		    {
			window.close();
		    }
		}

		/* Update */
		std::shared_ptr<GameState> current_state = state_manager.get_current_state();
		float dt = clock.restart().asSeconds();

		current_state->update(dt);

		/* Draw */
		window.clear(sf::Color::White);

		current_state->draw(&window);

		window.display();
	}
}
