#include <SFML/Graphics.hpp>
#include <iostream>
#include <tuple>
#include <vector>
#pragma once

class WallCollider {
	public: 
		sf::RectangleShape object;
		sf::Vector2f _position;

		WallCollider(sf::Vector2f _sendedPosition, sf::RectangleShape _sendedObject) {
			object = _sendedObject;
			_position = _sendedPosition;
		}
};

class Car {
	private:
		float _speed = 0.0, _maxSpeed = 0.0, _acceleration = 1000.0;
		bool _carMove = false, _accelerate = false;
		sf::Vector2f _speedVector, _position;
		std::vector<sf::Vector2f> _checkpoints;
	public:
		sf::Sprite object;

		Car(sf::Color &sendedCarColor, sf::Texture &carTexture, sf::Vector2f carPosition) {
			this->object.setTexture(carTexture);
			this->object.setColor(sendedCarColor);
			this->_position = sf::Vector2f(carPosition.x, carPosition.y);
		}

		void Move(int fps) {
			if (this->GetSpeed() == 0.0) { return; }
			float fpsFrame = 1.0 / fps;

			float carAngle = this->object.getRotation();
			carAngle = (carAngle >= 180) ? (carAngle - 360) : carAngle;
			carAngle *= (3.1415926 / 180);

			float vectorAngle = acos(GetSpeedVector().x) * (asin(GetSpeedVector().y >= 0) ? 1 : -1);
			sf::Vector2f resultVector(cos(carAngle + vectorAngle), sin(carAngle + vectorAngle));

			sf::Vector2f oldPosition = this->GetPosition();
			sf::Vector2f newPosition = oldPosition + sf::Vector2f(resultVector.x * GetSpeed() * fpsFrame,
				resultVector.y * GetSpeed() * fpsFrame);

			if ((oldPosition.x == newPosition.x) && (oldPosition.y == newPosition.y)) { return; }

			float nowAngle = this->object.getRotation() +
				GetSpeed() * fpsFrame * GetSpeedVector().x * ((GetSpeedVector().y >= 0) ? -1 : 1);

			this->_position = newPosition;
			this->object.setRotation(nowAngle);
		}

		void Acceleration(int fps) {
			float fpsFrame = 1.0 / fps;

			if (!this->_carMove) {
				// Машинка тормозит

				this->_accelerate = (this->GetSpeed() > 0.0);
				if (this->GetSpeed() > 0.0) {
					this->SetSpeedVector(0, this->GetSpeedVector().y);
					this->SetSpeed(this->GetSpeed() - this->_acceleration * fpsFrame);
				}
					
				return; 
			}

			if (this->GetSpeed() == this->GetMaxSpeed()) { return; }
			// Ускорять машинку

			this->SetSpeed(this->GetSpeed() + this->_acceleration * fpsFrame);
		}

		void SetMoveCheckpoints(std::vector<sf::Vector2f> *checkpoints) {
			this->_checkpoints = *checkpoints;
		}
		
		void SetSpeed(float newSpeed) {
			newSpeed = (newSpeed < 0.0) ? 0.0 : newSpeed;
			this->_speed = (newSpeed > this->GetMaxSpeed()) ? this->GetMaxSpeed() : newSpeed;
		}

		void SetMaxSpeed(float newMaxSpeed) {
			if (newMaxSpeed < 0.0) { return; }
			this->_maxSpeed = newMaxSpeed;
		}

		float GetMaxSpeed() {
			return this->_maxSpeed;
		}

		float GetSpeed() {
			return this->_speed;
		}

		void SetSpeedVector(float x, float y) {
			if (y == 0.0) {
				_carMove = false;
				return; 
			}

			float length = sqrt(x * x + y * y);

			sf::Vector2f oldVector(this->GetSpeedVector().x, this->GetSpeedVector().y);
			this->_speedVector = sf::Vector2f(x / length, y / length);

			_carMove = true;
			if (this->_accelerate) {
				this->_accelerate = false;

				if ( ((oldVector.y >= 0) ? 1 : -1) != ((this->_speedVector.y >= 0) ? 1 : -1) ) {
					this->SetSpeed(0);
				}
			}
		}

		sf::Vector2f GetSpeedVector() {
			return this->_speedVector;
		}

		sf::Vector2f GetPosition() {
			return this->_position;
;		}
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

	std::vector<sf::Vector2f> carsPositions;
	std::vector<sf::Color> carsColors;
	std::vector<Car> cars;

	std::vector<WallCollider> colliderWalls;
	std::vector<sf::Vector2f> checkpoints;

	int _exitChoice = 0;
	sf::Texture exitTexture;
	std::tuple<sf::Sprite, sf::Text, sf::Text, sf::Text> exitFrame;
};

GameContainer* GetContainer();