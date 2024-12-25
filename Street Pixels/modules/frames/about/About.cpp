#include "AboutHeader.h"
#include "objsContainer/AC_Header.h"
#include "../../other/keyboard/KeyboardHeader.h"

// Рендер меню
bool mouseButton = false;
void About_Render(sf::RenderWindow &window, int fps) {
	AboutContainer *container = GetContainer();
	container->fpsText.setString(std::to_string(fps));

	// Рендер
	window.draw(container->backgroundSprite_about);
	window.draw(container->fpsText);

	// Нажатие на кнопки
	if ((window.hasFocus()) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (!mouseButton)) {
		mouseButton = true;
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
	AboutContainer* container = GetContainer();
	container->exitSound.play();
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