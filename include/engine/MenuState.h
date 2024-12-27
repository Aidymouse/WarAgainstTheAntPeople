#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <engine/GameState.h>

class MenuState : public GameState {
public:
	void load() override;
	void update(float dt) override;
	void draw(sf::RenderTarget* render_target) override;
};
