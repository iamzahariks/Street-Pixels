#include "GMC_Header.h"

void makeTexts(std::vector < std::tuple<sf::Text, std::wstring, int, sf::Color, sf::Vector2f, sf::Font*>> *txts) {
	for (int i = 0; i < txts->size(); i++) {
		std::get<0>(txts->at(i)).setString(std::get<1>(txts->at(i)));
		std::get<0>(txts->at(i)).setCharacterSize(std::get<2>(txts->at(i)));
		std::get<0>(txts->at(i)).setFillColor(std::get<3>(txts->at(i)));
		std::get<0>(txts->at(i)).setPosition(std::get<4>(txts->at(i)));
		std::get<0>(txts->at(i)).setFont(*std::get<5>(txts->at(i)));
	}
}

GameMenuContainer _myContainer;
GameMenuContainer* GetContainer() {
	if (!_myContainer.isCreated) {
		_myContainer.isCreated = true;

		_myContainer.backgroundTexture.loadFromFile("imgs/gameMenu_background.png");
		_myContainer.background.setTexture(_myContainer.backgroundTexture);
		_myContainer.background.setScale(sf::Vector2f(2.0/3.0, 2.0/3.0));

		_myContainer.fpsFont.loadFromFile("fonts/EpilepsySans.ttf");
		_myContainer.font.loadFromFile("fonts/Sonic 1 Title Screen Filled.ttf");

		// FPS
		_myContainer.fpsText.setFillColor(sf::Color::Green);
		_myContainer.fpsText.setCharacterSize(26);
		_myContainer.fpsText.setFont(_myContainer.fpsFont);
		
		// Тексты
		_myContainer.textLabels.push_back({sf::Text(), L"Street Pixels", 36, sf::Color::Yellow, 
			sf::Vector2f(640, 60), &_myContainer.font});
		_myContainer.textLabels.push_back({ sf::Text(), L"Настройте матч по вашему желанию!", 26,
			sf::Color::Green, sf::Vector2f(640, 140), &_myContainer.font });
		_myContainer.textLabels.push_back({ sf::Text(), L"Количество ботов", 26, sf::Color::White,
			sf::Vector2f(640, 230), &_myContainer.font });
		_myContainer.textLabels.push_back({ sf::Text(), L"Скорость машин", 26, sf::Color::White,
			sf::Vector2f(640, 330), &_myContainer.font });

		// Кнопки
		_myContainer.buttons.push_back({ sf::Text(), L"0", 48, sf::Color::White,
			sf::Vector2f(640, 260), &_myContainer.fpsFont });
		_myContainer.buttons.push_back({ sf::Text(), L"6", 48, sf::Color::White,
			sf::Vector2f(640, 360), &_myContainer.fpsFont });
		_myContainer.buttons.push_back({ sf::Text(), L"Старт!", 52, sf::Color::White,
			sf::Vector2f(640, 500), &_myContainer.font });
		_myContainer.buttons.push_back({ sf::Text(), L"Выйти в меню", 26, sf::Color::White,
			sf::Vector2f(180, 640), &_myContainer.font });

		makeTexts(&_myContainer.textLabels);
		makeTexts(&_myContainer.buttons);
	}

	return &_myContainer;
}