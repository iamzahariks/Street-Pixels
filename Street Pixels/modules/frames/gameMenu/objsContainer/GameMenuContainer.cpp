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

		_myContainer.font.loadFromFile("fonts/EpilepsySans.ttf");

		// FPS
		_myContainer.fpsText.setFillColor(sf::Color::Green);
		_myContainer.fpsText.setCharacterSize(32);
		_myContainer.fpsText.setFont(_myContainer.font);
		
		// Тексты
		_myContainer.textLabels.push_back({sf::Text(), L"Street Pixels", 64, sf::Color::Yellow, 
			sf::Vector2f(640, 60), &_myContainer.font});
		_myContainer.textLabels.push_back({ sf::Text(), L"Настройте матч по вашему желанию!", 32,
			sf::Color::Cyan, sf::Vector2f(640, 140), &_myContainer.font });
		_myContainer.textLabels.push_back({ sf::Text(), L"Выйти в меню", 32, sf::Color::White,
			sf::Vector2f(120, 640), &_myContainer.font });
		makeTexts(&_myContainer.textLabels);
	}

	return &_myContainer;
}