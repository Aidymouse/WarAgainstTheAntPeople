#include "Tool.hpp"

#include "../Gamestate.hpp"

#include "../entities/Bomb.hpp"

class Bombs : public Tool {
public:
	Bombs::Bombs(std::string filename, float origin_x, float origin_y);
	void handle_event(sf::Event* event) override;
	sf::Texture bomb_tex;
};


Bombs::Bombs(std::string filename, float origin_x, float origin_y) : Tool::Tool(filename, origin_x, origin_y) {
	bomb_tex.loadFromFile((std::string)RESOURCE_PATH + "graphics/bomb sheet.png");
}

void Bombs::handle_event(sf::Event* event) {
	if (event->type == sf::Event::MouseButtonPressed) {
		if (event->mouseButton.button == sf::Mouse::Left) {
			Gamestate::insert_entity(std::shared_ptr<Bomb>(new Bomb(&bomb_tex, event->mouseButton.x, event->mouseButton.y)));
		}
	}
}

