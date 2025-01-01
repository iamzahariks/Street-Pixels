#include "HeaderFC.h"
#include "other/keyboard/KeyboardHeader.h"

#include "other/mouse/MouseHeader.h"
#include "frames/menu/MenuHeader.h"
#include "frames/game/GameHeader.h"
#include "frames/gameMenu/GameMenuHeader.h"
#include "frames/about/AboutHeader.h"

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
	std::string openedFrame = GetOpenedFrame();

	UpdateKeyboard(window, openedFrame);
	UpdateMouse(window, openedFrame);
	GetFrames()[openedFrame]->Render(window, fps);
};

// Получить открытое на данный момент окно
std::string GetOpenedFrame() {
	for (auto& gettedFrame : GetFrames()) {
		if ((gettedFrame.second->IsEnabled())) { return gettedFrame.second->frameName; }
	}

	return GetFrames()["menu"]->frameName;
}

struct FramesStorage {
	bool init = false;
	std::map <std::string, Frame*> frames;
};

struct FramesStorage storage;
// Получение всех окон приложения
std::map <std::string, Frame*> GetFrames() {
	if (!storage.init) {
		storage.init = true;
		storage.frames["gameMenu"] = GetGameMenu();
		storage.frames["game"] = GetGame();
		storage.frames["menu"] = GetMenu();
		storage.frames["about"] = GetAbout();
	}

	return storage.frames;
}