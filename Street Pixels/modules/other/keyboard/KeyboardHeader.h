#include <SFML/Graphics.hpp>
#include <vector>
#pragma once

typedef void(*keyboardFunc)(sf::RenderWindow&);

typedef std::tuple<sf::Keyboard::Key, bool,
	std::vector<int*>, std::vector<std::tuple<std::string, keyboardFunc>>> (_keyboardInfo);

typedef std::vector<_keyboardInfo>(_storageOfKeyboardFunctions);

void UpdateKeyboard(sf::RenderWindow& Window, std::string openedFrame);
int* KeyPressConnect(sf::Keyboard::Key key, std::string frameName, keyboardFunc function);
void KeyPressDisconnect(sf::Keyboard::Key key, int *id);
_keyboardInfo* GetKeyboardKey(sf::Keyboard::Key key);

bool KeyPressed(sf::Keyboard::Key key);
bool keyBoardExist(sf::Keyboard::Key key);