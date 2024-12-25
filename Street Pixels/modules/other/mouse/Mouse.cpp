#include "MouseHeader.h"
mouseConnectors _mouseInfo;

// Рендер мыши
void UpdateMouse(sf::RenderWindow& window, std::string frameName) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition() - window.getPosition();

	// Вход мыши в область
	for (hoverInfo& info : std::get<1>(_mouseInfo)) {
		if (std::get<0>(info) != frameName) { continue; }

		sf::Text *textObject = std::get<2>(info);

		sf::Vector2f txtPosition = textObject->getPosition();
		sf::Vector2f txtMinPosition = txtPosition + sf::Vector2f(-textObject->getLocalBounds().width / 2, 
			textObject->getCharacterSize() / 2);
		sf::Vector2f txtMaxPosition = txtPosition + sf::Vector2f(textObject->getLocalBounds().width / 2, 
			textObject->getLocalBounds().height + textObject->getCharacterSize());

		if ((mousePosition.x >= txtMinPosition.x) && (mousePosition.x <= txtMaxPosition.x)
			&& (mousePosition.y >= txtMinPosition.y) && (mousePosition.y <= txtMaxPosition.y)) {
			if (!std::get<1>(info)) {
				std::get<1>(info) = true;
				std::get<3>(info)(window);
			}
		}
		else {
			std::get<1>(info) = false;
		}
	}

	// Выход мыши из области
	for (hoverInfo& info : std::get<3>(_mouseInfo)) {
		if (std::get<0>(info) != frameName) { continue; }

		sf::Text* textObject = std::get<2>(info);

		sf::Vector2f txtPosition = textObject->getPosition();
		sf::Vector2f txtMinPosition = txtPosition + sf::Vector2f(-textObject->getLocalBounds().width / 2,
			textObject->getCharacterSize() / 2);
		sf::Vector2f txtMaxPosition = txtPosition + sf::Vector2f(textObject->getLocalBounds().width / 2,
			textObject->getLocalBounds().height + textObject->getCharacterSize());

		if ((mousePosition.x >= txtMinPosition.x) && (mousePosition.x <= txtMaxPosition.x)
			&& (mousePosition.y >= txtMinPosition.y) && (mousePosition.y <= txtMaxPosition.y)) {
			std::get<1>(info) = true;
		}
		else {
			if (std::get<1>(info)) { std::get<3>(info)(window); }
			std::get<1>(info) = false;
		}
	}

	// Нажатие мышкой по области
	for (clickInfo &info : std::get<5>(_mouseInfo)) {
		if ((std::get<0>(info) != frameName)) { continue; }
		if (LeftMousePressed() && !std::get<0>(_mouseInfo)) {
			sf::Text* textObject = std::get<1>(info);

			sf::Vector2f txtPosition = textObject->getPosition();
			sf::Vector2f txtMinPosition = txtPosition + sf::Vector2f(-textObject->getLocalBounds().width / 2,
				textObject->getCharacterSize() / 2);
			sf::Vector2f txtMaxPosition = txtPosition + sf::Vector2f(textObject->getLocalBounds().width / 2,
				textObject->getLocalBounds().height + textObject->getCharacterSize());

			if ((mousePosition.x >= txtMinPosition.x) && (mousePosition.x <= txtMaxPosition.x)
				&& (mousePosition.y >= txtMinPosition.y) && (mousePosition.y <= txtMaxPosition.y)) {
				std::get<2>(info)(window);
			}
		}
	}

	// Обновление нажатие мыши
	std::get<0>(_mouseInfo) = LeftMousePressed();
}

// Подключить функцию, когда мышь входит в область
int* ConnectMouseHoverFunc(std::string frameName, sf::Text *text, mouseFunc func) {
	std::get<1>(_mouseInfo).push_back(hoverInfo(frameName, false, text, func));

	int* newId = new int(std::get<1>(_mouseInfo).size() - 1);
	std::get<2>(_mouseInfo).push_back(newId);

	return std::get<2>(_mouseInfo).back();
}

// Отключить функцию, когда мышь входит в область
void DisconnectMouseHoverFunc(int *id) {
	std::get<1>(_mouseInfo).erase(std::next(std::get<1>(_mouseInfo).begin(), *id));
	
	for (int *connectorId : std::get<2>(_mouseInfo)) { 
		if (*connectorId < *id) continue;
		(*connectorId)--;
	}
}

// Подключить функцию, когда мышь выходит из области
int* ConnectMouseHoverLeaveFunc(std::string frameName, sf::Text* text, mouseFunc func) {
	std::get<3>(_mouseInfo).push_back(hoverInfo(frameName, false, text, func));

	int* newId = new int(std::get<3>(_mouseInfo).size() - 1);
	std::get<4>(_mouseInfo).push_back(newId);

	return std::get<4>(_mouseInfo).back();
}

// Отключить функцию, когда мышь входит в область
void DisconnectMouseHoverLeaveFunc(int* id) {
	std::get<3>(_mouseInfo).erase(std::next(std::get<3>(_mouseInfo).begin(), *id));

	for (int* connectorId : std::get<4>(_mouseInfo)) {
		if (*connectorId < *id) continue;
		(*connectorId)--;
	}
}

// Подключить функцию, когда происходит нажатие на область экрана
int* ConnectMouseClickFunc(std::string frameName, sf::Text *text, mouseFunc func) {
	std::get<5>(_mouseInfo).push_back(clickInfo(frameName, text, func));

	int* newId = new int(std::get<5>(_mouseInfo).size() - 1);
	std::get<6>(_mouseInfo).push_back(newId);

	return std::get<6>(_mouseInfo).back();
}
	
// Отключить функцию, когда происходит нажатие на область экрана
void DisconnectMouseClickFunc(int* id) {
	std::get<6>(_mouseInfo).erase(std::next(std::get<6>(_mouseInfo).begin(), *id));
	for (int *connectorId : std::get<6>(_mouseInfo)) {
		if (*connectorId < *id) continue;
		(*connectorId)--;
	}
}

// Нажато ли ЛКМ
bool LeftMousePressed() {
	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

// Нажато ли ПКМ
bool RightMousePressed() {
	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
}

// Получение позиции мышки
sf::Vector2i GetMousePosition() {
	return sf::Mouse::getPosition();
}