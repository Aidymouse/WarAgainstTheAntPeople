#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics/Texture.hpp>

enum TEX_IDX {
	GUY = 0,
	MALLET = 1,
};

namespace TextureStore {
	std::vector<sf::Texture> texture_store;
	
	void new_texture(std::string filename) {
		texture_store.emplace_back(sf::Texture(filename));
	}
	
}
