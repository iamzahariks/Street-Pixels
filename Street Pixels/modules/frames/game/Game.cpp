#include "GameHeader.h"
#include "objsContainer/GC_Header.h"

//Рендер игры
void GameRender(sf::RenderWindow &window, int fps) {
	GameContainer* container = GetContainer();

	container->fpsText.setString(std::to_string(fps));
	window.draw(container->fpsText);
	window.draw(container->testTxt);
}

void GameClose() {

}

Frame _createdGame;
Frame* GetGame() {
	if (_createdGame.frameName == "frame") {
		_createdGame.frameName = "game";

		_createdGame.Render = GameRender;
		_createdGame.Closing = GameClose;
	}

	return &_createdGame;
}