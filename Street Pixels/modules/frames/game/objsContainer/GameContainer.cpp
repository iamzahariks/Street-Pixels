#include "GC_Header.h"

GameContainer _myContainer;
GameContainer* GetContainer() {
	if (!_myContainer.isCreated) {
		_myContainer.isCreated = true;

		_myContainer.fpsFont.loadFromFile("fonts/EpilepsySans.ttf");
		_myContainer.font.loadFromFile("fonts/Sonic 1 Title Screen Filled.ttf");

		// Карта
		_myContainer._mapSprite.loadFromFile("imgs/map.png");
		_myContainer._mapImage.setTexture(_myContainer._mapSprite);
		_myContainer._mapImage.setScale(sf::Vector2f(2.5, 2.5));

		// Спрайт машин
		_myContainer._carSprite.loadFromFile("imgs/car.png");

		// Создание цветов машин
		_myContainer.carsColors.push_back(sf::Color::White);
		_myContainer.carsColors.push_back(sf::Color::Red);
		_myContainer.carsColors.push_back(sf::Color::Blue);
		_myContainer.carsColors.push_back(sf::Color::Green);
		_myContainer.carsColors.push_back(sf::Color::Yellow);

		// FPS
		_myContainer.fpsText.setFillColor(sf::Color::Green);
		_myContainer.fpsText.setCharacterSize(26);
		_myContainer.fpsText.setFont(_myContainer.fpsFont);

		// Настройка выхода из игры
		std::get<0>(_myContainer.exitFrame).setFillColor(sf::Color::White);
		std::get<0>(_myContainer.exitFrame).setSize(sf::Vector2f(500, 250));
		std::get<0>(_myContainer.exitFrame).setPosition(sf::Vector2f(640, 360));

		std::get<1>(_myContainer.exitFrame).setString(L"Вы хотите закончить игру?");
		std::get<1>(_myContainer.exitFrame).setFillColor(sf::Color::Black);
		std::get<1>(_myContainer.exitFrame).setFont(_myContainer.font);
		std::get<1>(_myContainer.exitFrame).setCharacterSize(20);
		std::get<1>(_myContainer.exitFrame).setPosition(sf::Vector2f(640, 300));

		std::get<2>(_myContainer.exitFrame).setString(L"Да");
		std::get<2>(_myContainer.exitFrame).setFillColor(sf::Color::Black);
		std::get<2>(_myContainer.exitFrame).setFont(_myContainer.font);
		std::get<2>(_myContainer.exitFrame).setCharacterSize(32);
		std::get<2>(_myContainer.exitFrame).setPosition(sf::Vector2f(560, 440));

		std::get<3>(_myContainer.exitFrame).setString(L"Нет");
		std::get<3>(_myContainer.exitFrame).setFillColor(sf::Color::Black);
		std::get<3>(_myContainer.exitFrame).setFont(_myContainer.font);
		std::get<3>(_myContainer.exitFrame).setCharacterSize(32);
		std::get<3>(_myContainer.exitFrame).setPosition(sf::Vector2f(720, 440));
	}

	return &_myContainer;
}