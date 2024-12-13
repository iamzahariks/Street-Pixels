#include "MenuHeader.h"
#include "objsContainer/MC_Header.h"
#include "../../HeaderFC.h"
#include "../../other/keyboard/KeyboardHeader.h"

// Рендер меню
void Menu_Render(sf::RenderWindow &window, int fps) {
	MenuContainer *container = GetContainer();

	// FPS
	container->fpsText.setString(std::to_string(fps));

	// Расстановки
	container->game.setOrigin(sf::Vector2f(container->game.getLocalBounds().width / 2,
		container->game.getLocalBounds().height / 2));

	for (int i = 0; i < 3; i++) {
		container->buttons[i].setFillColor(sf::Color::White);
		container->buttons[i].setOrigin(sf::Vector2f(container->buttons[i].getLocalBounds().width / 2,
			container->buttons[i].getLocalBounds().height / 2));
	}

	// Прочее
	container->buttons[container->choice].setFillColor(sf::Color::Red);

	// Рендер
	window.draw(container->fpsText);
	window.draw(container->game);

	for (int i = 0; i < 3; i++) {
		window.draw(container->buttons[i]);
	}
}

// Меню закрывается
void Menu_Closing() {
	MenuContainer* container = GetContainer();
	//container->choice = 0;
}

void Menu_ChoiceAdd(sf::RenderWindow &window) {
	MenuContainer* container = GetContainer();
	container->choice = (container->choice - 1 == -1) ? 2 : container->choice - 1;
}

void Menu_ChoiceRemove(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();
	container->choice = (container->choice + 1 == 3) ? 0 : container->choice + 1;
}

void Menu_Enter(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();

	switch (container->choice) {
		case(0): {
			break;
		}
		case(1): {
			OpenFrame("about");
			break;
		}
		case(2): {
			window.close();
			break;
		}
	}
}

Frame _createdMenu;
Frame* GetMenu() {
	if (_createdMenu.frameName == "frame") {
		_createdMenu.frameName = "menu";

		_createdMenu.Render = Menu_Render;
		_createdMenu.Closing = Menu_Closing;

		KeyPressConnect(sf::Keyboard::W, "menu", Menu_ChoiceAdd);
		KeyPressConnect(sf::Keyboard::Up, "menu", Menu_ChoiceAdd);

		KeyPressConnect(sf::Keyboard::S, "menu", Menu_ChoiceRemove);
		KeyPressConnect(sf::Keyboard::Down, "menu", Menu_ChoiceRemove);

		KeyPressConnect(sf::Keyboard::Enter, "menu", Menu_Enter);
	}

	return &_createdMenu;
}