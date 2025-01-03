#include "hmusic.h"

MusicContainer _myContainer;
MusicContainer* GetMusic() {
	if (!_myContainer.isCreated) {
		_myContainer.isCreated = true;
		_myContainer.aboutBuff.loadFromFile("sounds/about.wav");
		_myContainer.aboutSound.setBuffer(_myContainer.aboutBuff);
		_myContainer.aboutSound.setVolume(45.0);
		_myContainer.choiceBuff.loadFromFile("sounds/choice.wav");
		_myContainer.choiceSound.setBuffer(_myContainer.choiceBuff);
		_myContainer.choiceSound.setVolume(45.0);
		_myContainer.clickBuff.loadFromFile("sounds/click.wav");
		_myContainer.clickSound.setBuffer(_myContainer.clickBuff);
		_myContainer.clickSound.setVolume(45.0);
		_myContainer.exitBuff.loadFromFile("sounds/exit.wav");
		_myContainer.exitSound.setBuffer(_myContainer.exitBuff);
		_myContainer.exitSound.setVolume(45.0);
		_myContainer.victoryBuff.loadFromFile("sounds/victory.ogg");
		_myContainer.victory.setBuffer(_myContainer.victoryBuff);
		_myContainer.victory.setVolume(80.0);
		_myContainer.checkpointBuff.loadFromFile("sounds/checkpoint.ogg");
		_myContainer.checkpoint.setBuffer(_myContainer.checkpointBuff);
		_myContainer.checkpoint.setVolume(120.0);
		_myContainer.exitBuff.loadFromFile("sounds/exit.wav");
		_myContainer.exitSound.setBuffer(_myContainer.exitBuff);
		_myContainer.exitSound.setVolume(45.0);
		_myContainer.carExplosionBuff.loadFromFile("sounds/carExplosion.ogg");
		_myContainer.carExplosion.setBuffer(_myContainer.carExplosionBuff);
		_myContainer.carExplosion.setVolume(45.0);
		_myContainer.nitroBuff.loadFromFile("sounds/nitro.wav");
		_myContainer.nitroSound.setBuffer(_myContainer.nitroBuff);
		_myContainer.nitroSound.setVolume(45.0);
		_myContainer.music_menu.openFromFile("sounds/menu.ogg");
		_myContainer.music_menu.setVolume(36.0);
		_myContainer.game_music.openFromFile("sounds/gameMusic.wav");
		_myContainer.game_music.setVolume(36.0);
	}
	return &_myContainer;
}