#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

int main() {
	setlocale(LC_ALL, "RU");
	// Создание окна
	RenderWindow window(VideoMode(1280, 720), "Street Pixel");

	// Рендеринг
	while (window.isOpen()) {
		Event event;

		while (window.pollEvent(event)) {
			if (event.type != Event::Closed) { continue; }
			window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}
