#include <SFML/Graphics.hpp>
#include <iostream>
#include <tuple>
#include <vector>
#pragma once

struct GameMenuContainer {
	bool isCreated = false;

	sf::Text fpsText;

	std::vector < std::tuple<sf::Text, std::wstring, int, sf::Color, sf::Vector2f, sf::Font*> > textLabels;
	bool _rotateTextMatch = false;

	int choice = 0;
	std::vector < std::tuple<sf::Text, std::wstring, int, sf::Color, sf::Vector2f, sf::Font*> > buttons;

	sf::Font font;
};

GameMenuContainer* GetContainer();