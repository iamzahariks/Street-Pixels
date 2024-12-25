#include "AC_Header.h"

AboutContainer _myContainer;
AboutContainer* GetContainer() {
	if (!_myContainer.isCreated) {
		_myContainer.isCreated = true;

		_myContainer.font.loadFromFile("fonts/Sonic 1 Title Screen Filled.ttf");
		_myContainer.fps.loadFromFile("fonts/EpilepsySans.ttf");

		//Фон
		_myContainer.background_about.loadFromFile("imgs/about.png");
		_myContainer.backgroundSprite_about.setTexture(_myContainer.background_about);

		// FPS
		_myContainer.fpsText.setFillColor(sf::Color::Green);
		_myContainer.fpsText.setCharacterSize(26);
		_myContainer.fpsText.setFont(_myContainer.fps);

		// Звуки
		_myContainer.exitBuff.loadFromFile("sounds/about.wav");
		_myContainer.exitSound.setBuffer(_myContainer.exitBuff);
		_myContainer.exitSound.setVolume(44.0f);
	}

	return &_myContainer;
}