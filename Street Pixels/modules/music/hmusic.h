#include <SFML/Audio.hpp>
#pragma once

struct MusicContainer {
	bool isCreated = false;

	sf::SoundBuffer choiceBuff, clickBuff, exitBuff, aboutBuff, nitroBuff, carExplosionBuff, victoryBuff, checkpointBuff;
	sf::Sound choiceSound, clickSound, exitSound, aboutSound, nitroSound, carExplosion, victory, checkpoint;
	sf::Music music_menu, game_music;
};

MusicContainer* GetMusic();
