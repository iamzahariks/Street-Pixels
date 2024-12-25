#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#pragma once

struct AboutContainer {
	bool isCreated = false;

	sf::Texture background_about;
	sf::Sprite backgroundSprite_about;

	sf::Text fpsText;
	sf::Font font, fps;
	
	sf::SoundBuffer exitBuff;
	sf::Sound exitSound;
};

AboutContainer* GetContainer();