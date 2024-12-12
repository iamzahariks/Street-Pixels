#include "KeyboardHeader.h"
_storageOfKeyboardFunctions storageFunctions;

// Проверка нажатий
void UpdateKeyboard(sf::RenderWindow &window, std::string openedFrame) {
	for (_keyboardInfo &kInfo : storageFunctions) {
		if (!std::get<1>(kInfo) && (KeyPressed(std::get<0>(kInfo))) && (window.hasFocus())) {
			std::get<1>(kInfo) = true;
		}
		else {
			if ((!KeyPressed(std::get<0>(kInfo)) || (!window.hasFocus())) && (std::get<1>(kInfo))) {
				std::get<1>(kInfo) = false;
			}
			continue;
		}

		for (std::tuple<std::string, keyboardFunc> &frameInfo : std::get<2>(kInfo)) {
			if (std::get<0>(frameInfo).compare(openedFrame) != 0) { continue; }
			std::get<1>(frameInfo)(window);
		}
	}
}

// Нажатие на кнопку клавиатуры(подключение функции)
int KeyPressConnect(sf::Keyboard::Key key, std::string frameName, keyboardFunc function) {
	_keyboardInfo* keyboardKey = GetKeyboardKey(key);

	std::get<2>(*keyboardKey).push_back(std::tuple<std::string, keyboardFunc>(frameName, function));
	return std::get<2>(*keyboardKey).size() - 1;
}

// Нажатие на кнопку клавиатуры(отключение функции)
void KeyPressDisconnect(sf::Keyboard::Key key, int id) {
	if (!keyBoardExist(key)) { return; }
	_keyboardInfo keyboardKey = *GetKeyboardKey(key);
	std::get<2>(keyboardKey).erase( std::next(std::get<2>(keyboardKey).begin(), id) );
}

// Получить _keyboardInfo клавиши
_keyboardInfo* GetKeyboardKey(sf::Keyboard::Key key) {
	for (_keyboardInfo &kInfo : storageFunctions) {
		if (std::get<0>(kInfo) == key) { return &kInfo; }
	}

	storageFunctions.push_back({key, false, std::vector<std::tuple<std::string, keyboardFunc>>()});
	return &storageFunctions[storageFunctions.size() - 1];
}

// Зажата ли кнопка
bool KeyPressed(sf::Keyboard::Key key) {
	return sf::Keyboard::isKeyPressed(key);
}

// Существует ли _keyboardInfo клавиши
bool keyBoardExist(sf::Keyboard::Key key) {
	for (_keyboardInfo &kInfo : storageFunctions) {
		if (std::get<0>(kInfo) == key) { return true; }
	}

	return false;
}