#include <SFML/Graphics.hpp>
#include <iostream>
#include <tuple>
#include <vector>
#pragma once

class Car {
	private:
		float speed = 200.0;
		sf::Vector2f speedVector = sf::Vector2f(1.0/sqrt(2), 1.0/sqrt(2));
	public:
		sf::Sprite object;

		Car(sf::Color &sendedCarColor, sf::Texture &carTexture) {
			this->object.setTexture(carTexture);
			this->object.setColor(sendedCarColor);
		}

		float Move(int fps) {
			float fpsFrame = 1.0 / fps;
			
			sf::Vector2f oldPosition = this->object.getPosition();
			sf::Vector2f newPosition = oldPosition + sf::Vector2f(GetSpeedVector().x * GetSpeed() * fpsFrame,
				GetSpeedVector().y * GetSpeed() * fpsFrame);

			if ((oldPosition.x == newPosition.x) && (oldPosition.y == newPosition.y)) {
				return 0.0;
			}

			float angle = atan((newPosition.x - oldPosition.x) / (oldPosition.y - newPosition.y));
			angle *= (180 / 3.1415926);

			this->object.setPosition(newPosition);
			this->object.setRotation(angle);

			return (newPosition.x - oldPosition.x) / (oldPosition.y - newPosition.y);
		}

		void SetSpeed(float newSpeed, float maxSpeed) {
			this->speed = (newSpeed > maxSpeed) ? maxSpeed : newSpeed;
		}

		float GetSpeed() {
			return this->speed;
		}

		void SetSpeedVector(float x, float y) {
			float length = sqrt(x * x + y * y);
			this->speedVector = sf::Vector2f(x / length, y / length);
		}

		sf::Vector2f GetSpeedVector() {
			return this->speedVector;
		}
};

struct GameContainer {
	bool isCreated = false;

	bool _gamePaused = false;
	bool _gameStarted = false;
	int _countOfBots = 0;
	int _maxSpeed = 3;

	sf::Texture _carSprite;
	sf::Texture _mapSprite;
	sf::Sprite _mapImage;

	sf::Font fpsFont;
	sf::Font font;

	sf::Text fpsText;

	std::vector<sf::Color> carsColors;
	std::vector<Car> cars;

	int _exitChoice = 0;
	std::tuple<sf::RectangleShape, sf::Text, sf::Text, sf::Text> exitFrame;
};

GameContainer* GetContainer();