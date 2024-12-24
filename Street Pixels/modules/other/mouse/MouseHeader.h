#include <SFML/Graphics.hpp>
#include <vector>
#pragma once

typedef void(*mouseFunc)(sf::RenderWindow&);

typedef std::tuple<std::string, bool, sf::Text*, mouseFunc> (hoverInfo);
typedef std::vector<hoverInfo>(hoverStorage);

typedef std::tuple<std::string, sf::Text*, mouseFunc> (clickInfo);
typedef std::vector<clickInfo> (clickStorage);

typedef std::tuple<bool, hoverStorage, std::vector<int*>, clickStorage, std::vector<int*>>(mouseConnectors);

void UpdateMouse(sf::RenderWindow&, std::string);

int* ConnectMouseHoverFunc(std::string, sf::Text*, mouseFunc);
void DisconnectMouseHoverFunc(int *id);

int* ConnectMouseClickFunc(std::string, sf::Text*, mouseFunc);
void DisconnectMouseClickFunc(int *id);

bool LeftMousePressed();
sf::Vector2i GetMousePosition();