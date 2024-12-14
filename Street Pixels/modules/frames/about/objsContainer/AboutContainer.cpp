#include "AC_Header.h"

AboutContainer _myContainer;
AboutContainer* GetContainer() {
	if (!_myContainer.isCreated) {
		_myContainer.isCreated = true;

		_myContainer.font.loadFromFile("fonts/EpilepsySans.ttf");

		// FPS
		_myContainer.fpsText.setFillColor(sf::Color::Green);
		_myContainer.fpsText.setCharacterSize(32);
		_myContainer.fpsText.setFont(_myContainer.font);

		// Текст "Разработчики"
		_myContainer.devs.setFillColor(sf::Color::Yellow);
		_myContainer.devs.setCharacterSize(56);
		_myContainer.devs.setString(L"Разработчики проекта Street Pixels:");
		_myContainer.devs.setPosition(sf::Vector2f(1280 / 2, 50));
		_myContainer.devs.setFont(_myContainer.font);

		// Определение разработчиков
		for (int i = 0; i < 4; i++) {
			_myContainer.devsList[i].setFillColor(sf::Color::White);
			_myContainer.devsList[i].setCharacterSize(48);
			_myContainer.devsList[i].setString(_myContainer.devNames[i]);
			_myContainer.devsList[i].setPosition(sf::Vector2f(1280.0 / 2.0, 150.0 + i * 100.0));
			_myContainer.devsList[i].setFont(_myContainer.font);
		}

		// Текст "Выйти"
		_myContainer.exit.setFillColor(sf::Color::Red);
		_myContainer.exit.setCharacterSize(36);
		_myContainer.exit.setString(L"Выйти главное меню");
		_myContainer.exit.setPosition(sf::Vector2f(1280 / 2, 620));
		_myContainer.exit.setFont(_myContainer.font);

		// Звуки
		_myContainer.meowSoundBuff.loadFromFile("sounds/meow.wav");
		_myContainer.meowSound.setBuffer(_myContainer.meowSoundBuff);
		_myContainer.meowSound.setVolume(10.0f);
	}

	return &_myContainer;
}