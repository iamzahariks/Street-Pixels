#include "GC_Header.h"

WallCollider CreateRectangleByPositions(sf::Vector2f point1, sf::Vector2f point2) {
	sf::RectangleShape *shape = new sf::RectangleShape();

	shape->setSize(sf::Vector2f(abs(point2.x - point1.x), abs(point2.y - point1.y)));
	shape->setOrigin(sf::Vector2f(shape->getSize().x/2, shape->getSize().y / 2));
	shape->setFillColor(sf::Color::Red);

	sf::Vector2f pos((point1.x + point2.x) / 2, (point1.y + point2.y) / 2);
	WallCollider createdWall(pos, *shape);

	return createdWall;
}

GameContainer _myContainer;
GameContainer* GetContainer() {
	if (!_myContainer.isCreated) {
		_myContainer.isCreated = true;

		_myContainer.fpsFont.loadFromFile("fonts/EpilepsySans.ttf");
		_myContainer.font.loadFromFile("fonts/Sonic 1 Title Screen Filled.ttf");

		// Карта
		_myContainer._mapSprite.loadFromFile("imgs/map.png");
		_myContainer._mapImage.setTexture(_myContainer._mapSprite);
		_myContainer._mapImage.setScale(sf::Vector2f(2.5, 2.5));
		_myContainer._mapImage.setOrigin(
			sf::Vector2f(_myContainer._mapImage.getLocalBounds().width / 2,
				_myContainer._mapImage.getLocalBounds().height / 2)
		);

		// Спрайт машин
		_myContainer._carSprite.loadFromFile("imgs/car.png");

		// Создание цветов машин
		_myContainer.carsColors.push_back(sf::Color::White);

		// Расположение машин на карте
		_myContainer.carsPositions.push_back(sf::Vector2f(-1348.0, 1438));

		// Создание стен-коллайдеров
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-1795.63, -2274.92),
			sf::Vector2f(-1638.61, 2265.880)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-1801.60, -2272.0),
			sf::Vector2f(-605.335, -2124.78)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-607.53, -2294),
			sf::Vector2f(-364.711, -1884.82)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-364.4, -2035.31),
			sf::Vector2f(115.73, -2287.41)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-611, -1637),
			sf::Vector2f(-370, -1481)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-208, -1477),
			sf::Vector2f(-599, 669)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-599, 664),
			sf::Vector2f(-362, 1249)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-598, 1241),
			sf::Vector2f(349, 1719)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(355, 2126),
			sf::Vector2f(-581, 1967)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-1630, 2121),
			sf::Vector2f(1788, 2283)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(201, 1090),
			sf::Vector2f(356, 1716)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(200, 847),
			sf::Vector2f(354, 677)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(46, 688),
			sf::Vector2f(368, -1480)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(128, -2270),
			sf::Vector2f(368, -1480)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(368, -594),
			sf::Vector2f(1786, -740)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(1638, -602),
			sf::Vector2f(1800.76, 2163)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-1225, 1634),
			sf::Vector2f(-920, 1436)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-920, 1436),
			sf::Vector2f(-1187, 1249)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-1158, 1232),
			sf::Vector2f(-1005, 761)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-920, 751),
			sf::Vector2f(-1229, 368)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-1241, 109),
			sf::Vector2f(-923, 43)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-1229, -370),
			sf::Vector2f(-683, -432)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(-1160, -1012),
			sf::Vector2f(-898, -1462)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(759, -33),
			sf::Vector2f(1071, 270)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(1008, 278),
			sf::Vector2f(842, 755)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(1058, 771),
			sf::Vector2f(822, 936)));
		_myContainer.colliderWalls.push_back(CreateRectangleByPositions(sf::Vector2f(759, 1145),
			sf::Vector2f(1054, 943)));

		// FPS
		_myContainer.fpsText.setFillColor(sf::Color::Green);
		_myContainer.fpsText.setCharacterSize(26);
		_myContainer.fpsText.setFont(_myContainer.fpsFont);

		// Настройка выхода из игры
		_myContainer.exitTexture.loadFromFile("imgs/gameLeave.png");

		std::get<0>(_myContainer.exitFrame).setTexture(_myContainer.exitTexture);
		std::get<0>(_myContainer.exitFrame).setScale(sf::Vector2f(0.3, 0.3));
		std::get<0>(_myContainer.exitFrame).setPosition(sf::Vector2f(640, 360));
		std::get<0>(_myContainer.exitFrame).setOrigin(
			sf::Vector2f(std::get<0>(_myContainer.exitFrame).getLocalBounds().width / 2,
				std::get<0>(_myContainer.exitFrame).getLocalBounds().height / 2)
		);

		std::get<1>(_myContainer.exitFrame).setString(L"Вы хотите закончить игру?");
		std::get<1>(_myContainer.exitFrame).setFillColor(sf::Color::White);
		std::get<1>(_myContainer.exitFrame).setFont(_myContainer.font);
		std::get<1>(_myContainer.exitFrame).setCharacterSize(18);
		std::get<1>(_myContainer.exitFrame).setPosition(sf::Vector2f(640, 300));

		std::get<2>(_myContainer.exitFrame).setString(L"Да");
		std::get<2>(_myContainer.exitFrame).setFillColor(sf::Color::White);
		std::get<2>(_myContainer.exitFrame).setFont(_myContainer.font);
		std::get<2>(_myContainer.exitFrame).setCharacterSize(32);
		std::get<2>(_myContainer.exitFrame).setPosition(sf::Vector2f(560, 440));

		std::get<3>(_myContainer.exitFrame).setString(L"Нет");
		std::get<3>(_myContainer.exitFrame).setFillColor(sf::Color::White);
		std::get<3>(_myContainer.exitFrame).setFont(_myContainer.font);
		std::get<3>(_myContainer.exitFrame).setCharacterSize(32);
		std::get<3>(_myContainer.exitFrame).setPosition(sf::Vector2f(720, 440));
	}

	return &_myContainer;
}