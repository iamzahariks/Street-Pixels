#include "MC_Header.h"

MenuContainer _myContainer;
MenuContainer* GetContainer() {
	if (!_myContainer.isCreated) {
		_myContainer.isCreated = true;

		_myContainer.font.loadFromFile("fonts/EpilepsySans.ttf");

		// FPS
		_myContainer.fpsText.setFillColor(sf::Color::Green);
		_myContainer.fpsText.setCharacterSize(32);
		_myContainer.fpsText.setFont(_myContainer.font);

		// Текст Street Pixels
		_myContainer.game.setFillColor(sf::Color::Yellow);
		_myContainer.game.setCharacterSize(64);
		_myContainer.game.setString(L"Street Pixels");
		_myContainer.game.setPosition(sf::Vector2f(640, 60));
		_myContainer.game.setFont(_myContainer.font);

		// Кнопки
		for (int i = 0; i < 3; i++) {
			_myContainer.buttons[i].setFillColor(sf::Color::White);
			_myContainer.buttons[i].setCharacterSize(64);
			_myContainer.buttons[i].setString(_myContainer.buttonTexts[i]);
			_myContainer.buttons[i].setPosition(sf::Vector2f(640, 250 + 120 * i));
			_myContainer.buttons[i].setFont(_myContainer.font);
		}
	}

	return &_myContainer;
}