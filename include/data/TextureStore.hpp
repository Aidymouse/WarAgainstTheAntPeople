#pragma once

#include <string>
#include <SFML/Graphics/Texture.hpp>

#include <ProjectConfig.h>


namespace TextureStore {

	const sf::Texture GUY = sf::Texture(std::string(GRAPHICS_PATH).append("guy sheet.png"));
	const sf::Texture MALLET = sf::Texture(std::string(GRAPHICS_PATH).append("mallet.png"));
}
