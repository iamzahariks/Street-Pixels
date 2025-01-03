#include <SFML/Audio.hpp>
#pragma once

struct MusicContainer {
	bool isCreated = false;

	sf::SoundBuffer choiceBuff, clickBuff, exitBuff, aboutBuff, nitroBuff;
	sf::Sound choiceSound, clickSound, exitSound, aboutSound, nitroSound;
	sf::Music music_menu, game_music;
};

MusicContainer* GetMusic();
