#include <SFML/Graphics.hpp>
#pragma once

struct MenuContainer {
	bool isCreated = false;

	sf::Text fpsText;
	sf::Text game;

	int choice = 0;
	sf::Text buttons[3] = { sf::Text(), sf::Text(), sf::Text()  };
	std::wstring buttonTexts[3] = {
		L"Играть",
		L"О нас",
		L"Выйти",
	};

	sf::Font font;
};

MenuContainer* GetContainer();