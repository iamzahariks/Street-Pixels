#include "GameHeader.h"
#include "objsContainer/GC_Header.h"
#include "../../music/hmusic.h"
#include "../../other/keyboard/KeyboardHeader.h"
#include "../../other/mouse/MouseHeader.h"

//Рендер
float x, y;
void Game_Render(sf::RenderWindow &window, int fps) {
	GameContainer* container = GetContainer();

	// FPS
	float _fpsValue = (fps / 144.0 > 1.0) ? (1.0) : (fps / 144.0);
	container->fpsText.setFillColor(sf::Color(255 - (int)(_fpsValue * 255), 255 - (255 - (int)(_fpsValue * 255)), 0, 255));
	container->fpsText.setString(std::to_string(fps));
	
	// Движение игрока
	if (!container->_gamePaused) {
		x = 0.0; y = 0.0;

		x += (((KeyPressed(sf::Keyboard::A) || (KeyPressed(sf::Keyboard::Left)))) ? -0.3 : 0);
		x += (((KeyPressed(sf::Keyboard::D) || (KeyPressed(sf::Keyboard::Right)))) ? 0.3 : 0);

		y += (((KeyPressed(sf::Keyboard::W) || (KeyPressed(sf::Keyboard::Up)))) ? -1.0 : 0);
		y += (((KeyPressed(sf::Keyboard::S) || (KeyPressed(sf::Keyboard::Down)))) ? 1.0 : 0);

		container->cars.at(0).SetSpeedVector(x, y);
	}

	// Движение машин
	for (int i = 0; i < container->cars.size(); i++) {
		if (!container->_gamePaused) {
			container->cars.at(i).Acceleration(fps);
			container->cars.at(i).Move(fps);
		}
	}

	// Обновить положение карты
	Car userCar = container->cars.at(0);
	sf::Vector2f carPosition(userCar.GetPosition().x, userCar.GetPosition().y);
	container->_mapImage.setPosition(sf::Vector2f(640.0, 360.0) - carPosition);
	container->fpsText.setString(std::to_string(carPosition.x) + ' ' + std::to_string(carPosition.y));
	
	// Обновить положение других машин
	for (int i = 1; i < container->cars.size(); i++) {
		container->cars.at(i).object.setPosition(container->_mapImage.getPosition() + container->cars.at(i).GetPosition());
	}

	// Обновить положение стен-коллайдеров
	for (int i = 0; i < container->colliderWalls.size(); i++) {
		container->colliderWalls.at(i).object.setPosition(container->_mapImage.getPosition() 
			+ container->colliderWalls.at(i)._position);
	}

	// Рендер
	window.draw(container->_mapImage);

	for (int i = 0; i < container->colliderWalls.size(); i++) {
		window.draw(container->colliderWalls.at(i).object);
	}

	for (int i = 0; i < container->cars.size(); i++) {
		window.draw(container->cars.at(i).object);
	}

	// Рендер меню выхода
	if (container->_gamePaused) {
		std::get<1>(container->exitFrame).setOrigin(
			sf::Vector2f(std::get<1>(container->exitFrame).getLocalBounds().width / 2,
				std::get<1>(container->exitFrame).getLocalBounds().height / 2)
		);
		
		std::get<2>(container->exitFrame).setOrigin(
			sf::Vector2f(std::get<2>(container->exitFrame).getLocalBounds().width / 2,
				std::get<2>(container->exitFrame).getLocalBounds().height / 2)
		);
		
		std::get<3>(container->exitFrame).setOrigin(
			sf::Vector2f(std::get<3>(container->exitFrame).getLocalBounds().width / 2,
				std::get<3>(container->exitFrame).getLocalBounds().height / 2)
		);

		std::get<2>(container->exitFrame).setFillColor(sf::Color::White);
		std::get<3>(container->exitFrame).setFillColor(sf::Color::White);
		
		if (container->_exitChoice == 0) {
			std::get<2>(container->exitFrame).setFillColor(sf::Color::Red);
		}
		else {
			std::get<3>(container->exitFrame).setFillColor(sf::Color::Red);
		}

		window.draw(std::get<0>(container->exitFrame));
		window.draw(std::get<1>(container->exitFrame));
		window.draw(std::get<2>(container->exitFrame));
		window.draw(std::get<3>(container->exitFrame));
	}

	window.draw(container->fpsText);
}



// Отправить настройки игры
void Game_LoadSettingsToGame(int countOfBots, int maxSpeed) {
	GameContainer* container = GetContainer();
	container->_countOfBots = countOfBots;
	container->_maxSpeed = maxSpeed;

	container->cars.clear();
	for (int i = 0; i < countOfBots + 1; i++) {
		container->cars.push_back(Car(container->carsColors.at(i), container->_carSprite, container->carsPositions.at(i)));

		if (i == 0) {
			container->cars.at(i).object.setPosition(sf::Vector2f(640.0, 360.0));
			container->cars.at(i).SetMaxSpeed(maxSpeed);
		}
		else {
			container->cars.at(i).SetMaxSpeed(maxSpeed - ((rand() % 10) / 20.0 * maxSpeed));
		}

		container->cars.at(i).object.setOrigin(sf::Vector2f(
			container->cars.at(i).object.getLocalBounds().width / 2,
			container->cars.at(i).object.getLocalBounds().height / 2)
		);
	}
}

// Выход из игры
void Game_Close() {
	GetContainer()->_gameStarted = false;
	GetContainer()->_gamePaused = false;
	GetContainer()->_exitChoice = 0;
}



// Игрок нажал Escape
void Game_EscapePressed(sf::RenderWindow& window) {
	GameContainer* container = GetContainer();

	if (container->_gamePaused) {
		container->_gamePaused = false;
		container->_exitChoice = 0;
		return;
	}

	container->_gamePaused = true;
}

// Игрок нажал Enter
void Game_EnterPressed(sf::RenderWindow& window) {
	GameContainer* container = GetContainer();

	if (container->_gamePaused) {
		GetMusic()->choiceSound.play();

		if (container->_exitChoice == 0) {
			OpenFrame("menu");
		}
		else {
			container->_exitChoice = 0;
			container->_gamePaused = false;
		}

		return;
	}
}



// Игрок нажал A или Left
void Game_Left(sf::RenderWindow& window) {
	GameContainer* container = GetContainer();

	if (container->_gamePaused) {
		container->_exitChoice = (container->_exitChoice - 1 == -1) ? (1) : (container->_exitChoice - 1);
		GetMusic()->choiceSound.play();
		return;
	}
}

// Игрок нажал D или Right
void Game_Right(sf::RenderWindow& window) {
	GameContainer* container = GetContainer();

	if (container->_gamePaused) {
		container->_exitChoice = (container->_exitChoice + 1 == 2) ? (0) : (container->_exitChoice + 1);
		GetMusic()->choiceSound.play();
		return;
	}
}

// Выделение кнопки "Да" в меню выхода
void Game_ExitYesHover(sf::RenderWindow& window) {
	GameContainer* container = GetContainer();
	container->_exitChoice = 0;
	GetMusic()->choiceSound.play();
}

// Нажатие кнопки "Да" в меню выхода
void Game_ExitYesClick(sf::RenderWindow& window) {
	GetMusic()->choiceSound.play();
	OpenFrame("menu");
}



// Выделение кнопки "Нет" в меню выхода
void Game_ExitNoHover(sf::RenderWindow& window) {
	GameContainer* container = GetContainer();
	container->_exitChoice = 1;
	GetMusic()->choiceSound.play();
}

// Нажатие кнопки "Нет" в меню выхода
void Game_ExitNoClick(sf::RenderWindow& window) {
	GameContainer* container = GetContainer();

	GetMusic()->clickSound.play();
	container->_exitChoice = 0;
	container->_gamePaused = false;
}


Frame _createdGame;
Frame* GetGame() {
	if (_createdGame.frameName == "frame") {
		_createdGame.frameName = "game";

		KeyPressConnect(sf::Keyboard::Escape, "game", Game_EscapePressed);
		KeyPressConnect(sf::Keyboard::Enter, "game", Game_EnterPressed);

		KeyPressConnect(sf::Keyboard::Left, "game", Game_Left);
		KeyPressConnect(sf::Keyboard::A, "game", Game_Left);

		KeyPressConnect(sf::Keyboard::Right, "game", Game_Right);
		KeyPressConnect(sf::Keyboard::D, "game", Game_Right);

		ConnectMouseClickFunc("game", &std::get<2>(GetContainer()->exitFrame), Game_ExitYesClick);
		ConnectMouseHoverFunc("game", &std::get<2>(GetContainer()->exitFrame), Game_ExitYesHover);

		ConnectMouseClickFunc("game", &std::get<3>(GetContainer()->exitFrame), Game_ExitNoClick);
		ConnectMouseHoverFunc("game", &std::get<3>(GetContainer()->exitFrame), Game_ExitNoHover);

		_createdGame.Render = Game_Render;
		_createdGame.Closing = Game_Close;
	}

	return &_createdGame;
}