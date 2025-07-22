
#pragma once

#include <iostream>
#include <string>

#include <ProjectConfig.h>
#include <SDL3/SDL.h>
#include <unordered_map>

#include <anim/Anim.hpp>
#include <data/TextureStore.hpp>

class AnimStore {
private:
	AnimStore() {};
	// AnimStore(AnimStore const &);
	// void operator=(AnimStore const &);

public:
	std::unordered_map<std::string, AnimFrame> animations;

	static AnimStore &getInstance() {
		static AnimStore instance;
		return instance;
	};

	AnimStore(AnimStore const &) = delete;
	void operator=(AnimStore const &) = delete;

	void load_animation(std::string animation_id, std::string texture_id, SDL_FRect rect, float duration, xy offset) {
		std::cout << "...loading animation '" << animation_id << "' using '" << texture_id << "'" << std::endl;

  		TextureStore &texture_store = TextureStore::getInstance();

		AnimFrame frame = {
			texture_store.get(texture_id),
			rect,
			duration,
			nullptr, // Can be loaded later
			offset
		};

		animations[animation_id] = frame;

	}

	AnimFrame get(std::string animation_name) { return animations[animation_name]; }

	void set_next_animation(std::string animation_id, std::string next_id) {
		animations[animation_id].next_frame = &animations[next_id];
	}

};
