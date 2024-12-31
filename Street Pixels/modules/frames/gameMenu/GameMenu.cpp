#include "GameMenuHeader.h"
#include "objsContainer/GMC_Header.h"
#include "../../other/keyboard/KeyboardHeader.h"
#include "../../other/mouse/MouseHeader.h"

//Рендер игры
void GameMenuRender(sf::RenderWindow &window, int fps) {
	GameMenuContainer* container = GetContainer();

	// FPS
	container->fpsText.setString(std::to_string(fps));

	// Расстановки
	for (int i = 0; i < container->textLabels.size(); i++) {
		std::get<0>(container->textLabels[i]).setOrigin(
			sf::Vector2f(std::get<0>(container->textLabels[i]).getLocalBounds().width / 2, 0));
	}

	for (int i = 0; i < container->buttons.size(); i++) {
		std::get<0>(container->buttons[i]).setOrigin(
			sf::Vector2f(std::get<0>(container->buttons[i]).getLocalBounds().width / 2, 0));
	}

	// Вращение текста "Настройте матч"
	if (!container->_rotateTextMatch) {
		float _newRotation = std::get<0>(container->textLabels[1]).getRotation();
		_newRotation = (_newRotation >= 180) ? (_newRotation - 360) : _newRotation;
		_newRotation += (1.0 / fps) * 6;

		std::get<0>(container->textLabels[1]).setRotation(_newRotation);
		container->_rotateTextMatch = (_newRotation >= 5.0) ? true : false;
	}
	else {
		float _newRotation = std::get<0>(container->textLabels[1]).getRotation();
		_newRotation = (_newRotation >= 180) ? (_newRotation - 360) : _newRotation;
		_newRotation -= (1.0 / fps) * 6;

		std::get<0>(container->textLabels[1]).setRotation(_newRotation);
		container->_rotateTextMatch = (_newRotation <= -5.0) ? false : true;
	}
	//

	// Рендер
	window.draw(container->fpsText);
	for (int i = 0; i < container->textLabels.size(); i++) {
		window.draw(std::get<0>(container->textLabels[i]));
	}

	for (int i = 0; i < container->buttons.size(); i++) {
		window.draw(std::get<0>(container->buttons[i]));
	}
}

void GameMenuClose() {
	GetContainer()->choice = 0;
}



void GameMenu_OpenMenu(sf::RenderWindow &window) {
	OpenFrame("menu");
}

void GameMenu_LeaveButton_Hover(sf::RenderWindow& window) {
	std::get<0>(GetContainer()->textLabels.at(2)).setFillColor(sf::Color::Red);
}

void GameMenu_LeaveButton_HoverLeave(sf::RenderWindow& window) {
	std::get<0>(GetContainer()->textLabels.at(2)).setFillColor(sf::Color::White);
}



void GameMenu_Enter(sf::RenderWindow& window) {
	GameMenuContainer* container = GetContainer();
}

void GameMenu_ChoiceAdd(sf::RenderWindow& window) {
	GameMenuContainer* container = GetContainer();
	container->choice = (container->choice - 1 == -1) ? 2 : container->choice - 1;
}

void GameMenu_ChoiceRemove(sf::RenderWindow& window) {
	GameMenuContainer* container = GetContainer();
	container->choice = (container->choice + 1 == container->buttons.size()) ? 0 : container->choice + 1;
}



Frame _createdGame;
Frame* GetGameMenu() {
	if (_createdGame.frameName == "frame") {
		_createdGame.frameName = "gameMenu";

		KeyPressConnect(sf::Keyboard::Enter, "gameMenu", GameMenu_Enter);
		KeyPressConnect(sf::Keyboard::W, "gameMenu", GameMenu_ChoiceRemove);
		KeyPressConnect(sf::Keyboard::Up, "gameMenu", GameMenu_ChoiceRemove);
		KeyPressConnect(sf::Keyboard::S, "gameMenu", GameMenu_ChoiceAdd);
		KeyPressConnect(sf::Keyboard::Down, "gameMenu", GameMenu_ChoiceAdd);

		KeyPressConnect(sf::Keyboard::Escape, "gameMenu", GameMenu_OpenMenu);
		ConnectMouseClickFunc("gameMenu", &(std::get<0>(GetContainer()->textLabels.at(2))), GameMenu_OpenMenu);

		ConnectMouseHoverFunc("gameMenu", &(std::get<0>(GetContainer()->textLabels.at(2))), GameMenu_LeaveButton_Hover);
		ConnectMouseHoverLeaveFunc("gameMenu", &(std::get<0>(GetContainer()->textLabels.at(2))), 
			GameMenu_LeaveButton_HoverLeave);

		_createdGame.Render = GameMenuRender;
		_createdGame.Closing = GameMenuClose;
	}

	return &_createdGame;
}