#include "Game.h"
#include <iostream>
#include "../logic/StateMgr.h"
#include "Player.h"
#include "Wall.h"
#include "../logic/EntityMgr.h"
#include "../logic/World.h"

#include <fstream>
#include <sstream>

sf::RenderWindow Game::window;

Game::Game() {
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Meat Boy");
	StateMgr::getInstance(); // Lazy initialization

	loadLevel(); // for now load a level directly, then menu and then loadlevel
};

void Game::loadLevel() {
	EntityMgr::getInstance()->addEntity(Player::getInstance());

	int tileSize = TILESIZE * SCALE;

	std::ifstream level;
	level.open("levels/level-1/level-1.csv");

	std::string line;
	char delimiter = ',';

	std::string value;
	int row = 0; // top
	int column = 0; // left
	while (getline(level, line)) { /* read entire line into line */
		std::stringstream ss(line); /* create stringstream from line */
		while (getline(ss, value, delimiter)) { /* read each field from line */
			Vec2 pos(row * tileSize, column * tileSize);
			if (value != "-1")
				EntityMgr::getInstance()->addEntity(new Wall(pos));
			//else if (value == "1") // end
			row++;
		}
		column++;
		row = 0;
	}
}

void Game::run() {
    Stopwatch* stopwatch = Stopwatch::getInstance();
    while (window.isOpen()) {
        if (stopwatch->timeSinceLastUpdate() > TIME_PER_FRAME) {
            stopwatch->reset();
            process();
        }
        render();
    }
}

void Game::process() {
	/*if (StateMgr::getInstance()->isInMenuState()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed: {
				handleMenuInput(event.key.code);
			} break;
			default:
				break;
			}
		}
	}
	else {*/
	sf::Event event{};
	while (window.pollEvent(event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed) window.close();
	}
	Player::getInstance()->update();
	//}
}

void Game::render() {
    window.clear();
	EntityMgr::getInstance()->drawAll();
    window.display();
}

void Game::handleMenuInput(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
		std::cout << "Selecting up" << std::endl;
	else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
		std::cout << "Selecting down" << std::endl;
}
