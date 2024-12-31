#include <SFML/Graphics.hpp>
#include "modules/HeaderFC.h"

int main() {
    // Создание окна игры
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Street Pixel", sf::Style::Fullscreen);
    OpenFrame("menu");

    //Изменение курсора
    sf::Cursor cursor; sf::Image cursorImage; 
    cursorImage.loadFromFile("imgs/cursor.png"); 
    cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 50));
    window.setMouseCursor(cursor);

    // Счётчики FPS
    window.setFramerateLimit(144);
    sf::Clock fpsClock;
    int fps = 144;
    
    //Добавление иконки приложения
    sf::Image icon;
    if (!icon.loadFromFile("imgs/icon.png")){
        return 1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    


    // Рендер
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        Render(window, fps);
        window.display();

        fps = 1000 / fpsClock.getElapsedTime().asMilliseconds();
        fpsClock.restart();
    }

    return 0;
}


