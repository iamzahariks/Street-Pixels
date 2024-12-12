#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#pragma once

struct AboutContainer {
	bool isCreated = false;

	sf::Text fpsText;
	sf::Text devs;

	sf::Text devsList[4] = { sf::Text(), sf::Text(), sf::Text(), sf::Text() };
	std::wstring devNames[4] = {
		L"Позняк Захар Сергеевич",
		L"Ильясеевич Роман Сергеевич",
		L"Говоронок Роман Юрьевич",
		L"Плитко Максим Андреевич", 
	};

	sf::Text exit;
	sf::Font font;
	
	sf::SoundBuffer meowSoundBuff;
	sf::Sound meowSound;
};

AboutContainer* GetContainer();