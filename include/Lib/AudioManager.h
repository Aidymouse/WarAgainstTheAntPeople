#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <iostream>
#include <map>
#include <queue>

#pragma once
class AudioManager {

public:
	static std::map<std::string, sf::SoundBuffer> sound_buffers;

	static std::queue<sf::Sound> sounds;

	static void update(float dt);
	static void load_sound(std::string sound_name, std::string filename);
	static void play_sound(std::string sound_name);
};

