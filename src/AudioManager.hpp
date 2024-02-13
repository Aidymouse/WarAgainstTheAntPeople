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

std::map<std::string, sf::SoundBuffer> AudioManager::sound_buffers;
std::queue<sf::Sound> AudioManager::sounds;

// If there are multiple sounds that are done, only one will be removed each frame
// In addition, a stopped sound can get stuck behind a playing sound.
// But also all sounds are quite short so hopefully it doesn't matter
void AudioManager::update(float dt) {
	if (sounds.size() == 0) return;
	if (sounds.front().getStatus() == sf::Sound::Status::Stopped) {
		sounds.pop();
	}
}

void AudioManager::load_sound(std::string sound_name, std::string filename) {
	sound_buffers[sound_name].loadFromFile(filename);
}

void AudioManager::play_sound(std::string sound_name) {
	if (sounds.size() > 200) { return; }
	sf::Sound new_sound;

	new_sound.setBuffer(sound_buffers[sound_name]);
	sounds.push(new_sound);
	sounds.back().play();
}
