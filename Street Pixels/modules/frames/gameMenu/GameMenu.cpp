#include "GameMenuHeader.h"
#include "objsContainer/GMC_Header.h"
#include "../../music/hmusic.h"
#include "../game/GameHeader.h"
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
		std::get<0>(container->buttons[i]).setFillColor(std::get<3>(container->buttons[i]));
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

	// Изменение цвета кнопок при наведении
	std::get<0>(container->buttons[container->choice]).setFillColor(sf::Color::Red);

	// Назначить новые значения строк в кнопках
	std::get<0>(container->buttons[0]).setString(std::to_string(container->maxSpeed));

	// Рендер
	window.draw(container->background);
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
	GetContainer()->maxSpeed = 500;
}


void GameMenu_StartGame(sf::RenderWindow& window) {
	Game_LoadSettingsToGame(GetContainer()->maxSpeed);
	OpenFrame("game");
}

void GameMenu_OpenMenu(sf::RenderWindow &window) {
	OpenFrame("menu");
}



void GameMenu_MaxSpeed_Hover(sf::RenderWindow& window) {
	GetContainer()->choice = 0;
	GetMusic()->choiceSound.play();
}

void GameMenu_Start_Hover(sf::RenderWindow& window) {
	GetContainer()->choice = 1;
	GetMusic()->choiceSound.play();
}

void GameMenu_LeaveButton_Hover(sf::RenderWindow& window) {
	GetContainer()->choice = 2;
	GetMusic()->choiceSound.play();
}



void GameMenu_Enter(sf::RenderWindow& window) {
	GameMenuContainer* container = GetContainer();

	switch (container->choice) {
		case(1): {
			GameMenu_StartGame(window);
			GetMusic()->clickSound.play();
			break;
		}
		case(2): {
			GameMenu_OpenMenu(window);
			GetMusic()->clickSound.play();
			break;
		}
	}
}

void GameMenu_AddValues(sf::RenderWindow& window) {
	GameMenuContainer* container = GetContainer();
	GetMusic()->clickSound.play();

	switch (container->choice) {
		case(0): {
			int newValue = container->maxSpeed + 25;
			container->maxSpeed = (newValue > 10000) ? 10000 : newValue;
			break;
		}
	}
}

void GameMenu_RemoveValues(sf::RenderWindow& window) {
	GameMenuContainer* container = GetContainer();
	GetMusic()->clickSound.play();

	switch (container->choice) {
		case(0): {
			int newValue = container->maxSpeed - 25;
			container->maxSpeed = (newValue < 10) ? 10 : newValue;
			break;
		}
	}
}



void GameMenu_ChoiceAdd(sf::RenderWindow& window) {
	GameMenuContainer* container = GetContainer();
	GetMusic()->choiceSound.play();
	container->choice = (container->choice - 1 == -1) ? 2 : container->choice - 1;
}

void GameMenu_ChoiceRemove(sf::RenderWindow& window) {
	GameMenuContainer* container = GetContainer();
	GetMusic()->choiceSound.play();
	container->choice = (container->choice + 1 == container->buttons.size()) ? 0 : container->choice + 1;
}



Frame _createdGameMenu;
Frame* GetGameMenu() {
	if (_createdGameMenu.frameName == "frame") {
		_createdGameMenu.frameName = "gameMenu";

		KeyPressConnect(sf::Keyboard::Enter, "gameMenu", GameMenu_Enter);
		KeyPressConnect(sf::Keyboard::W, "gameMenu", GameMenu_ChoiceAdd);
		KeyPressConnect(sf::Keyboard::Up, "gameMenu", GameMenu_ChoiceAdd);
		KeyPressConnect(sf::Keyboard::S, "gameMenu", GameMenu_ChoiceRemove);
		KeyPressConnect(sf::Keyboard::Down, "gameMenu", GameMenu_ChoiceRemove);
		KeyPressConnect(sf::Keyboard::Escape, "gameMenu", GameMenu_OpenMenu);

		KeyPressConnect(sf::Keyboard::Right, "gameMenu", GameMenu_AddValues);
		KeyPressConnect(sf::Keyboard::D, "gameMenu", GameMenu_AddValues);

		KeyPressConnect(sf::Keyboard::Left, "gameMenu", GameMenu_RemoveValues);
		KeyPressConnect(sf::Keyboard::A, "gameMenu", GameMenu_RemoveValues);

		ConnectMouseHoverFunc("gameMenu", &(std::get<0>(GetContainer()->buttons.at(0))), GameMenu_MaxSpeed_Hover);

		ConnectMouseClickFunc("gameMenu", &(std::get<0>(GetContainer()->buttons.at(1))), GameMenu_Enter);
		ConnectMouseHoverFunc("gameMenu", &(std::get<0>(GetContainer()->buttons.at(1))), GameMenu_Start_Hover);

		ConnectMouseClickFunc("gameMenu", &(std::get<0>(GetContainer()->buttons.at(2))), GameMenu_Enter);
		ConnectMouseHoverFunc("gameMenu", &(std::get<0>(GetContainer()->buttons.at(2))), GameMenu_LeaveButton_Hover);

		_createdGameMenu.Render = GameMenuRender;
		_createdGameMenu.Closing = GameMenuClose;
	}

	return &_createdGameMenu;
}