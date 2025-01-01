#include <SFML/Graphics.hpp>
#include <iostream>
#include <tuple>
#include <vector>
#pragma once

struct GameContainer {
	bool isCreated = false;

	bool _gamePaused = false;
	bool _gameStarted = false;
	int _countOfBots = 0;
	int _maxSpeed = 3;

	sf::Texture _carSprite;
	sf::Texture _mapSprite;
	sf::Sprite _mapImage;

	sf::Font fpsFont;
	sf::Font font;

	sf::Text fpsText;

	std::vector<sf::Color> carsColors;
	std::vector<sf::Sprite> cars;

	int _exitChoice = 0;
	std::tuple<sf::RectangleShape, sf::Text, sf::Text, sf::Text> exitFrame;
};

GameContainer* GetContainer();