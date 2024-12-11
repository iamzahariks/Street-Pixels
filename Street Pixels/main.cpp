#include <SFML/Graphics.hpp>
#include "modules/HeaderFC.h"

int main() {
	// —оздание окна игры
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Street Pixels", sf::Style::Default);
	OpenFrame("menu");

	// —чЄтчики FPS
	window.setFramerateLimit(144);
	sf::Clock fpsClock;
	int fps = 0;

	// –ендер
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
		}

		window.clear();
		Render(window, fps);
		window.display();

		fps = 1000 / fpsClock.getElapsedTime().asMilliseconds();
		fpsClock.restart();
	}

	return 0;
}