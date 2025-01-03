#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#pragma once
	
void UpdateFrames(std::string);
void OpenFrame(std::string);
void Render(sf::RenderWindow &window, int);
std::string GetOpenedFrame();

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
		
	// Закрыть фрейм(самостоятельно лучше не использовать данный метод)
	void Close() {
		isEnabled = false;
		Closing();
	}

	// !!! Функция рендера, которую необходимо заполнить в каждом отдельном фрейме
	// самостоятельно !!!
	void (*Render)(sf::RenderWindow&, int fps);
	void (*Closing)();

	// Открыт ли фрейм
	bool IsEnabled() {
		return isEnabled;
	}
};

std::map <std::string, Frame*> GetFrames();