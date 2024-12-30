#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#pragma once

struct AboutContainer {
	bool isCreated = false;

	sf::Texture background_about;
	sf::Sprite backgroundSprite_about;

	sf::Text fpsText;
	sf::Font font, fps;
};

AboutContainer* GetContainer();