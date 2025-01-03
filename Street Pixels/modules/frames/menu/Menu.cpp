#include "MenuHeader.h"
#include "../../music/hmusic.h"
#include "objsContainer/MC_Header.h"
#include "../../other/keyboard/KeyboardHeader.h"
#include "../../other/mouse/MouseHeader.h"

// Рендер меню
void Menu_Render(sf::RenderWindow &window, int fps) {
	MenuContainer *container = GetContainer();
	
	//Background
	container->backgroundSprite_menu.setScale(2.0f, 1.5f);
	window.draw(container->backgroundSprite_menu);
	

	// FPS
	container->fpsText.setString(std::to_string(fps));
	
	// Кнопки

	for (int i = 0; i < 3; i++) {
		container->buttons[i].setFillColor(sf::Color::White);
		container->buttons[i].setOrigin(sf::Vector2f(container->buttons[i].getLocalBounds().width / 2, 0));
	}


	// Изменение цвета кнопок при наведении
	container->buttons[container->choice].setFillColor(sf::Color::Red);
		
	// FPS
	window.draw(container->fpsText);

	for (int i = 0; i < 3; i++) {
		window.draw(container->buttons[i]);
	}

}

// Пролистование
void Menu_Closing() {
	MenuContainer* container = GetContainer();
	container->choice = 0;
}

void Menu_ChoiceAdd(sf::RenderWindow &window) {
	MenuContainer* container = GetContainer();
	container->choice = (container->choice - 1 == -1) ? 2 : container->choice - 1;
	MusicContainer* music = GetMusic();
	music->choiceSound.play();
}

void Menu_ChoiceRemove(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();
	container->choice = (container->choice + 1 == 3) ? 0 : container->choice + 1;
	MusicContainer* music = GetMusic();
	music->choiceSound.play();
}


// Выбор Play
void Menu_PlayHover(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();
	MusicContainer* music = GetMusic();
	music->choiceSound.play();
	GetContainer()->choice = 0;
}

// Выбор About
void Menu_AboutHover(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();
	MusicContainer* music = GetMusic();
	music->choiceSound.play();
	GetContainer()->choice = 1;
}

// Выбор EXIT
void Menu_ExitHover(sf::RenderWindow& window){
	MenuContainer* container = GetContainer();
	MusicContainer* music = GetMusic();
	music->choiceSound.play();
	GetContainer()->choice = 2;
}



// Play
void Menu_PlayClick(sf::RenderWindow& window) {
	MusicContainer* music = GetMusic();
	music->clickSound.play();
	OpenFrame("gameMenu");
}

// About
void Menu_AboutClick(sf::RenderWindow& window) {
	MusicContainer* music = GetMusic();
	music->clickSound.play();
	OpenFrame("about");
}

// Exit
void Menu_ExitClick(sf::RenderWindow& window) {
	MusicContainer* music = GetMusic();
	music->music_menu.setVolume(30);
	music->exitSound.play();
	sf::sleep(sf::milliseconds(1300));
	window.close();
}



void Menu_Enter(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();
	MusicContainer* music = GetMusic();

	switch (container->choice) {
		case(0): {
			music->clickSound.play();
			OpenFrame("gameMenu");
			break;
		}
		case(1): {
			music->clickSound.play();
			OpenFrame("about");
			break;
		}
		case(2): {
			music->music_menu.setVolume(30);
			music->exitSound.play();
			sf::sleep(sf::milliseconds(1350));
			window.close();
			break;
		}
	}
}

Frame _createdMenu;
Frame* GetMenu() {
	if (_createdMenu.frameName == "frame") {
		_createdMenu.frameName = "menu";

		MusicContainer* music = GetMusic();
		music->music_menu.setLoop(true);
		music->music_menu.play();

		_createdMenu.Render = Menu_Render;
		_createdMenu.Closing = Menu_Closing;

		KeyPressConnect(sf::Keyboard::W, "menu", Menu_ChoiceAdd);
		KeyPressConnect(sf::Keyboard::Up, "menu", Menu_ChoiceAdd);

		KeyPressConnect(sf::Keyboard::S, "menu", Menu_ChoiceRemove);
		KeyPressConnect(sf::Keyboard::Down, "menu", Menu_ChoiceRemove);

		KeyPressConnect(sf::Keyboard::Enter, "menu", Menu_Enter);

		ConnectMouseHoverFunc("menu", &(GetContainer()->buttons[0]), Menu_PlayHover);
		ConnectMouseClickFunc("menu", &(GetContainer()->buttons[0]), Menu_PlayClick);

		ConnectMouseHoverFunc("menu", &(GetContainer()->buttons[1]), Menu_AboutHover);
		ConnectMouseClickFunc("menu", &(GetContainer()->buttons[1]), Menu_AboutClick);

		ConnectMouseHoverFunc("menu", &(GetContainer()->buttons[2]), Menu_ExitHover);
		ConnectMouseClickFunc("menu", &(GetContainer()->buttons[2]), Menu_ExitClick);

	}

	return &_createdMenu;
}