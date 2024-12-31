#include <SFML/Graphics.hpp>
#pragma once

struct MenuContainer {
	bool isCreated = false;

	sf::Texture background_menu;
	sf::Sprite backgroundSprite_menu;
	sf::Text fpsText;

	sf::Font font, fps;

	int choice = 0;
	sf::Text buttons[3] = { sf::Text(), sf::Text(), sf::Text()  };

	std::wstring buttonTexts[3] = {
		L"Играть",
		L"О нас",
		L"Выйти",
	};
};

MenuContainer* GetContainer();