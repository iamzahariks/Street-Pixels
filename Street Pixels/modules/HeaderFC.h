#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#pragma once
	
void UpdateFrames(std::string);
void OpenFrame(std::string);
void Render(sf::RenderWindow &window, int);

class Frame {
private:
	bool isEnabled = false;
public:
	std::string frameName = "frame";

	// Открыть фрейм: закрывает все предыдущие, учитывайте это!
	void Open() {
		isEnabled = true;
		UpdateFrames(frameName);
	}
	
	// Закрыть фрейм, самостоятельно лучше не использовать данный метод.
	void Close() {
		isEnabled = false;
	}

	// !!! Функция рендера, которую необходимо заполнить в каждом отдельном фрейме
	// самостоятельно !!!
	void (*Render)(sf::RenderWindow&, int fps);

	// Открыт ли фрейм
	bool IsEnabled() {
		return isEnabled;
	}
};

std::map <std::string, Frame*> GetFrames();