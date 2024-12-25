#include "MenuHeader.h"
#include "objsContainer/MC_Header.h"
#include "../../other/keyboard/KeyboardHeader.h"
#include "../../other/mouse/MouseHeader.h"

// Ðåíäåð ìåíþ
void Menu_Render(sf::RenderWindow &window, int fps) {
	MenuContainer *container = GetContainer();
	
	//Background
	container->backgroundSprite_menu.setScale(2.0f, 1.5f);
	window.draw(container->backgroundSprite_menu);
	

	// FPS
	container->fpsText.setString(std::to_string(fps));
	
	// Ðàññòàíîâêè

	for (int i = 0; i < 3; i++) {
		container->buttons[i].setFillColor(sf::Color::White);
		container->buttons[i].setOrigin(sf::Vector2f(container->buttons[i].getLocalBounds().width / 2, 0));
	}


	// Ïðî÷åå
	container->buttons[container->choice].setFillColor(sf::Color::Red);
		
	// Ðåíäåð
	window.draw(container->fpsText);

	for (int i = 0; i < 3; i++) {
		window.draw(container->buttons[i]);
	}

}

// Ìåíþ çàêðûâàåòñÿ
void Menu_Closing() {
	MenuContainer* container = GetContainer();
	container->choice = 0;
}

void Menu_ChoiceAdd(sf::RenderWindow &window) {
	MenuContainer* container = GetContainer();
	container->choice = (container->choice - 1 == -1) ? 2 : container->choice - 1;
	container->choiceSound.play();
}

void Menu_ChoiceRemove(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();
	container->choice = (container->choice + 1 == 3) ? 0 : container->choice + 1;
	container->choiceSound.play();
}


// Âûäåëåíèå êíîïêè Play
void Menu_PlayHover(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();
	container->choiceSound.play();
	GetContainer()->choice = 0;
}

// Âûäåëåíèå êíîïêè About
void Menu_AboutHover(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();
	container->choiceSound.play();
	GetContainer()->choice = 1;
}

// Âûäåëåíèå êíîïêè âûõîäà
void Menu_ExitHover(sf::RenderWindow& window){
	MenuContainer* container = GetContainer();
	container->choiceSound.play();
	GetContainer()->choice = 2;
}



// Íàæàòèå ïî êíîïêå Play
void Menu_PlayClick(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();
	container->clickSound.play();
	OpenFrame("gameMenu");
}

// Íàæàòèå ïî êíîïêå About
void Menu_AboutClick(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();
	container->clickSound.play();
	OpenFrame("about");
}

// Íàæàòèå ïî êíîïêå Exit
void Menu_ExitClick(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();
	container->music_menu.setVolume(27.0f);
	container->exitSound.play();
	sf::sleep(sf::milliseconds(1300));
	window.close();
}



void Menu_Enter(sf::RenderWindow& window) {
	MenuContainer* container = GetContainer();

	switch (container->choice) {
		case(0): {
			container->clickSound.play();
			OpenFrame("gameMenu");
			break;
		}
		case(1): {
			container->clickSound.play();
			OpenFrame("about");
			break;
		}
		case(2): {
			container->music_menu.setVolume(26.0f);
			container->exitSound.play();
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

		MenuContainer* container = GetContainer();
		container->music_menu.setLoop(true);
		container->music_menu.play();

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