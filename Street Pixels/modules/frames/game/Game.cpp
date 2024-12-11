#include "GameHeader.h"

struct GameContainer {

};

GameContainer _myContainer;
GameContainer GetContainer() {
	return _myContainer;
}

//Рендер игры
void GameRender(sf::RenderWindow &window, int fps) {

}

Frame _createdGame;
Frame* GetGame() {
	if (_createdGame.frameName == "frame") {
		_createdGame.frameName = "game";
		_createdGame.Render = GameRender;
	}

	return &_createdGame;
}