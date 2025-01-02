#include <SFML/Audio.hpp>
#pragma once

struct MusicContainer {
	bool isCreated = false;

	sf::SoundBuffer choiceBuff, clickBuff, exitBuff, aboutBuff;
	sf::Sound choiceSound, clickSound, exitSound, aboutSound;
	sf::Music music_menu, game_music;
};

MusicContainer* GetMusic();
