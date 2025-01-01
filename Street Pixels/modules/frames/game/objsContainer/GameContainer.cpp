#include "GC_Header.h"

GameContainer _myContainer;
GameContainer* GetContainer() {
	if (!_myContainer.isCreated) {
		_myContainer.isCreated = true;

		_myContainer.fpsFont.loadFromFile("fonts/EpilepsySans.ttf");
		_myContainer.font.loadFromFile("fonts/Sonic 1 Title Screen Filled.ttf");

		// FPS
		_myContainer.fpsText.setFillColor(sf::Color::Green);
		_myContainer.fpsText.setCharacterSize(26);
		_myContainer.fpsText.setFont(_myContainer.fpsFont);

		// Настройка выхода из игры
		std::get<0>(_myContainer.exitFrame).setFillColor(sf::Color::White);
		std::get<0>(_myContainer.exitFrame).setSize(sf::Vector2f(500, 250));
		std::get<0>(_myContainer.exitFrame).setPosition(sf::Vector2f(640, 360));
	}

	return &_myContainer;
}