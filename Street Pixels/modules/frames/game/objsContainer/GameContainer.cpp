#include "GC_Header.h"

GameContainer _myContainer;
GameContainer* GetContainer() {
	if (!_myContainer.isCreated) {
		_myContainer.isCreated = true;

		_myContainer.font.loadFromFile("fonts/EpilepsySans.ttf");

		// FPS
		_myContainer.fpsText.setFillColor(sf::Color::Green);
		_myContainer.fpsText.setCharacterSize(32);
		_myContainer.fpsText.setFont(_myContainer.font);
		
		// Тестовое сообщение
		_myContainer.testTxt.setFillColor(sf::Color::Yellow);
		_myContainer.testTxt.setCharacterSize(64);
		_myContainer.testTxt.setString(L"Тестовое сообщение!");
		_myContainer.testTxt.setPosition(sf::Vector2f(544, 180));
		_myContainer.testTxt.setFont(_myContainer.font);
	}

	return &_myContainer;
}