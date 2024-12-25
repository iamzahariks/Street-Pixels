#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#pragma once

struct MenuContainer {
	bool isCreated = false;

	sf::Text fpsText;
	sf::Texture background_menu;
	sf::Sprite backgroundSprite_menu;


	int choice = 0;
	sf::Text buttons[3] = { sf::Text(), sf::Text(), sf::Text()  };

	std::wstring buttonTexts[3] = {
		L"Играть",
		L"О нас",
		L"Выйти",
	};

	sf::Font font, fps;

	sf::SoundBuffer choiceBuff, clickBuff, exitBuff;
	sf::Sound choiceSound, clickSound, exitSound;
	sf::Music music_menu;
};

MenuContainer* GetContainer();