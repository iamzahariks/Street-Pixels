#include "MenuHeader.h"

struct MenuContainer {
	bool isCreated = false;

	sf::Text fpsText;
	sf::Text play;
	sf::Text info;
	sf::Text left;

	sf::Font font;
};

MenuContainer _myContainer;
MenuContainer* GetContainer() {
	if (!_myContainer.isCreated) {
		_myContainer.isCreated = true;

		_myContainer.font.loadFromFile("fonts/EpilepsySans.ttf");

		_myContainer.fpsText.setFillColor(sf::Color::Green);
		_myContainer.fpsText.setCharacterSize(32);
		_myContainer.fpsText.setFont(_myContainer.font);

		_myContainer.play.setFillColor(sf::Color::White);
		_myContainer.play.setCharacterSize(64);
		_myContainer.play.setString(L"Играть");
		_myContainer.play.setPosition(sf::Vector2f(544, 180));
		_myContainer.play.setFont(_myContainer.font);

		_myContainer.info.setFillColor(sf::Color::White);
		_myContainer.info.setCharacterSize(64);
		_myContainer.info.setString(L"О нас");
		_myContainer.info.setPosition(sf::Vector2f(544, 320));
		_myContainer.info.setFont(_myContainer.font);

		_myContainer.left.setFillColor(sf::Color::White);
		_myContainer.left.setCharacterSize(64);
		_myContainer.left.setString(L"Выйти");
		_myContainer.left.setPosition(sf::Vector2f(544, 460));
		_myContainer.left.setFont(_myContainer.font);
	}

	return &_myContainer;
}

// Рендер меню
void MenuRender(sf::RenderWindow &window, int fps) {
	MenuContainer *container = GetContainer();

	container->fpsText.setString(std::to_string(fps));
	window.draw(container->fpsText);
	window.draw(container->play);
	window.draw(container->info);
	window.draw(container->left);
}

Frame _createdMenu;
Frame* GetMenu() {
	if (_createdMenu.frameName == "frame") {
		_createdMenu.frameName = "menu";
		_createdMenu.Render = MenuRender;
	}

	return &_createdMenu;
}