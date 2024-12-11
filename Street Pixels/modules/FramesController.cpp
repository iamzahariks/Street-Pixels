#include "HeaderFC.h"
#include "frames/menu/MenuHeader.h"
#include "frames/game/GameHeader.h"

// Обновления окон при открытии нового окна
void UpdateFrames(std::string frameName) {
	for (auto &gettedFrame : GetFrames()) {
		if (gettedFrame.first == frameName) { continue; }
		if (!gettedFrame.second->IsEnabled()) { continue; }

		gettedFrame.second->Close();
		break;
	}
}

// Открыть окно через имя
void OpenFrame(std::string frameName) {
	GetFrames()[frameName]->Open();
}

// Функция рендера окна
void Render(sf::RenderWindow &window, int fps) {
	for (auto& gettedFrame : GetFrames()) {
		if ( (! gettedFrame.second->IsEnabled()) ) { continue; }
		gettedFrame.second->Render(window, fps);
		break;
	}
};

struct FramesStorage {
	bool init = false;
	std::map <std::string, Frame*> frames;
};

struct FramesStorage storage;
// Получение всех окон приложения
std::map <std::string, Frame*> GetFrames() {
	if (!storage.init) {
		storage.init = true;
		storage.frames["game"] = GetGame();
		storage.frames["menu"] = GetMenu();
	}

	return storage.frames;
}