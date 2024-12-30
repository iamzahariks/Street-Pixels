#include "hmusic.h"

MusicContainer _myContainer;
MusicContainer* GetMusic() {
	if (!_myContainer.isCreated) {
		_myContainer.isCreated = true;
		_myContainer.aboutBuff.loadFromFile("sounds/about.wav");
		_myContainer.aboutSound.setBuffer(_myContainer.aboutBuff);
		_myContainer.aboutSound.setVolume(44.0f);
		_myContainer.choiceBuff.loadFromFile("sounds/choice.wav");
		_myContainer.choiceSound.setBuffer(_myContainer.choiceBuff);
		_myContainer.choiceSound.setVolume(44.0f);
		_myContainer.clickBuff.loadFromFile("sounds/click.wav");
		_myContainer.clickSound.setBuffer(_myContainer.clickBuff);
		_myContainer.clickSound.setVolume(44.0f);
		_myContainer.clickBuff.loadFromFile("sounds/click.wav");
		_myContainer.clickSound.setBuffer(_myContainer.clickBuff);
		_myContainer.clickSound.setVolume(44.0f);
		_myContainer.exitBuff.loadFromFile("sounds/exit.wav");
		_myContainer.exitSound.setBuffer(_myContainer.exitBuff);
		_myContainer.exitSound.setVolume(79.0f);
		_myContainer.music_menu.openFromFile("sounds/menu.ogg");
		_myContainer.music_menu.setVolume(38.0f);
	}
	return &_myContainer;
}