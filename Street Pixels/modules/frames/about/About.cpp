#include "AboutHeader.h"
#include "objsContainer/AC_Header.h"
#include "../../other/keyboard/KeyboardHeader.h"

// Рендер меню
bool mouseButton = false;
void About_Render(sf::RenderWindow &window, int fps) {
	AboutContainer *container = GetContainer();
	container->fpsText.setString(std::to_string(fps));

	// Расстановка текста
	container->devs.setOrigin(sf::Vector2f(container->devs.getLocalBounds().width / 2, 
		container->devs.getLocalBounds().height / 2));

	container->exit.setOrigin(sf::Vector2f(container->exit.getLocalBounds().width / 2,
		container->exit.getLocalBounds().height / 2));

	// Рендер
	window.draw(container->fpsText);
	window.draw(container->devs);

	for (int i = 0; i < 4; i++) {
		std::string devId = "dev" + std::to_string(i);
		container->devsList[i].setOrigin(sf::Vector2f(container->devsList[i].getLocalBounds().width / 2,
			container->devsList[i].getLocalBounds().height / 2));

		window.draw(container->devsList[i]);
	}

	window.draw(container->exit);

	// Нажатие на кнопки
	if ((window.hasFocus()) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (!mouseButton)) {
		mouseButton = true;
		container->meowSound.play();
	}
	else {
		if ((!sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (mouseButton)) {
			mouseButton = false;
		}
	}
}

// Меню закрывается
void About_Closing() {
	mouseButton = false;
}

// Закрыть информацию о нас
void About_Leave(sf::RenderWindow& window) {
	OpenFrame("menu");
};

Frame _createdAbout;
Frame* GetAbout() {
	if (_createdAbout.frameName == "frame") {
		_createdAbout.frameName = "about";

		_createdAbout.Render = About_Render;
		_createdAbout.Closing = About_Closing;

		KeyPressConnect(sf::Keyboard::Enter, "about", About_Leave);
	}

	return &_createdAbout;
}