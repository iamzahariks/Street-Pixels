#include "MC_Header.h"

MenuContainer _myContainer;
MenuContainer* GetContainer() {
	if (!_myContainer.isCreated){
		_myContainer.isCreated = true;
		_myContainer.fps.loadFromFile("fonts/EpilepsySans.ttf");
		_myContainer.font.loadFromFile("fonts/Sonic 1 Title Screen Filled.ttf");

		//Background
		_myContainer.background_menu.loadFromFile("imgs/STREET PIXEL.jpg");
		_myContainer.backgroundSprite_menu.setTexture(_myContainer.background_menu);

		// FPS
		_myContainer.fpsText.setFillColor(sf::Color::Green);
		_myContainer.fpsText.setCharacterSize(26);
		_myContainer.fpsText.setFont(_myContainer.fps);

		// Кнопки
		for (int i = 0; i < 3; i++) {
			_myContainer.buttons[i].setFillColor(sf::Color::White);
			_myContainer.buttons[i].setCharacterSize(36);
			_myContainer.buttons[i].setLetterSpacing(1.3f);
			_myContainer.buttons[i].setOutlineThickness(4);
			_myContainer.buttons[i].setOutlineColor(sf::Color::Black);
			_myContainer.buttons[i].setString(_myContainer.buttonTexts[i]);
			_myContainer.buttons[i].setPosition(sf::Vector2f(1160.0, 510.0 + 72.0 * i));
			_myContainer.buttons[i].setFont(_myContainer.font);
		}
	}

	return &_myContainer;
}