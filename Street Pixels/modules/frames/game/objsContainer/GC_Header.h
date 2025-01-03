#include <SFML/Graphics.hpp>
#include <iostream>
#include <tuple>
#include <vector>
#pragma once


// Класс стены-коллайдера
class WallCollider {
	public: 
		sf::RectangleShape object;
		sf::Vector2f _position;

		WallCollider(sf::Vector2f _sendedPosition, sf::RectangleShape _sendedObject) {
			object = _sendedObject;
			_position = _sendedPosition;
		}
};

// Класс машины
class Car {
	private:
		float _speed = 0.0, _maxSpeed = 0.0, _acceleration = 1000.0, _checkpointValue = 0;
		bool _carMove = false, _checkPointRotate = false, _accelerate = false, _shiftEnabled = false;
		sf::Vector2f _speedVector;
		std::vector<sf::Vector2f> _checkpoints;
	public:
		sf::Vector2f _position;
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

		int CarInZone(std::vector<WallCollider> *zones) {
			std::vector<sf::Vector2f> pointsOfCar;

			sf::Vector2f carSize = this->object.getLocalBounds().getSize();
			sf::Vector2f carPosition = this->GetPosition();

			sf::Vector2f carLookVector = this->GetLookVector();
			sf::Vector2f carRightVector = this->GetRightVector();

			for (int i = -1; i <= 1; i += 2) {
				for (int v = -1; v <= 1; v += 2) {
					pointsOfCar.push_back(carPosition 
						+ sf::Vector2f(carLookVector.x * i * carSize.y/2, carLookVector.y * i * carSize.y / 2) 
						+ sf::Vector2f(carRightVector.x * v * carSize.x / 2, carRightVector.y * v * carSize.x / 2));
				}
			}

			for (int wallIndex = 0; wallIndex < zones->size(); wallIndex++) {
				sf::Vector2f sizeOfWall = zones->at(wallIndex).object.getLocalBounds().getSize();

				sf::Vector2f point2 = zones->at(wallIndex)._position + sf::Vector2f(sizeOfWall.x/2, sizeOfWall.y/2);
				sf::Vector2f point1 = zones->at(wallIndex)._position - sf::Vector2f(sizeOfWall.x/2, sizeOfWall.y/2);

				for (int carPointIndex = 0; carPointIndex < pointsOfCar.size(); carPointIndex++) {
					sf::Vector2f carPoint = pointsOfCar.at(carPointIndex);

					if (carPoint.x >= point1.x && carPoint.x <= point2.x
						&& carPoint.y >= point1.y && carPoint.y <= point2.y) 
					{
						return (carPointIndex <= 1) ? (1) : (-1);
					}
				}
			}

			return 0;
		}
		
		void Acceleration(int fps) {
			float fpsFrame = 1.0 / fps;

			//if (this->_checkpoints.size() > 0) {
			//	// Машина - это бот, которого нужно вести по траектории

			//	int checkpointValue = this->_checkpointValue;
			//	sf::Vector2f checkpoint = this->_checkpoints[checkpointValue];
			//	sf::Vector2f carPos = this->GetPosition();

			//	float carAngle = this->object.getRotation();
			//	carAngle = (carAngle >= 180) ? (carAngle - 360) : carAngle;
			//	carAngle *= (3.1415926 / 180);

			//	int distance = sqrt(pow(carPos.x - checkpoint.x, 2) + pow(carPos.y - checkpoint.y, 2));
			//	sf::Vector2f speedVector(checkpoint.x - carPos.x, checkpoint.y - carPos.y);

			//	if (distance < 20) {
			//		this->_checkPointRotate = true;

			//		sf::Vector2f nextCheckpoint = this->_checkpoints[(checkpointValue + 1) % this->_checkpoints.size()];
			//		speedVector += sf::Vector2f(nextCheckpoint.x - carPos.x, nextCheckpoint.y - carPos.y);
			//	}

			//	int lengthOfVector = sqrt(speedVector.x * speedVector.x + speedVector.y * speedVector.y);
			//	speedVector = sf::Vector2f(speedVector.x / lengthOfVector, speedVector.y / lengthOfVector);

			//	float speedVectorAngle = acos(speedVector.x) * ((asin(speedVector.y) >= 0) ? (1) : (-1));
			//	speedVector = sf::Vector2f(cos(speedVectorAngle - carAngle), sin(speedVectorAngle + carAngle));

			//	this->SetSpeedVector(speedVector.x, speedVector.y);
			//}

			if (this->_carMove == false) {
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
		
		void ShiftPressed() {
			if (this->_shiftEnabled) return;
			this->_shiftEnabled = true;
			this->_acceleration += 1500;
			this->_maxSpeed += 150;
		}

		void ShiftUnPressed() {
			if (!this->_shiftEnabled) return;
			this->_shiftEnabled = false;
			this->_acceleration -= 1500;
			this->_maxSpeed -= 150;
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

		sf::Vector2f GetLookVector() {
			float carAngle = this->object.getRotation();
			carAngle = (carAngle >= 180) ? (carAngle - 360) : carAngle;
			carAngle -= 90;
			carAngle *= (3.1415926 / 180);

			return sf::Vector2f(cos(carAngle), sin(carAngle));
		}

		sf::Vector2f GetRightVector() {
			float carAngle = this->object.getRotation();
			carAngle = (carAngle >= 180) ? (carAngle - 360) : carAngle;
			carAngle *= (3.1415926 / 180);

			return sf::Vector2f(cos(carAngle), sin(carAngle));
		}

		void SetSpeedVector(float x, float y) {
			if (y == 0.0) {
				_carMove = false;
				return; 
			}

			float savedOldY = (this->GetSpeedVector().y >= 0.0) ? 1.0 : -1.0;

			float length = sqrt(x * x + y * y);
			this->_speedVector = sf::Vector2f(x / length, y / length);

			float savedNewY = (this->_speedVector.y >= 0.0) ? 1.0 : -1.0;

			_carMove = true;
			if (this->_accelerate) {
				if (savedOldY != savedNewY) {
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
	sf::Texture _mapSprite, _mapBack;
	sf::Sprite _mapImage, _mapBackImage;

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