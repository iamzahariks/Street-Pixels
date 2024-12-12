#include <SFML/Graphics.hpp>
#pragma once

struct GameContainer {
	bool isCreated = false;

	sf::Text fpsText;
	sf::Text testTxt;

	sf::Font font;
};

GameContainer* GetContainer();