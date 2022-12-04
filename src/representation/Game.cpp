#include "Game.h"
#include <iostream>
#include "../logic/StateMgr.h"
#include "Player.h"
#include "Wall.h"
#include "../logic/World.h"
#include "LevelEnd.h"
#include "../logic/Camera.h"

#include <fstream>
#include <sstream>

sf::RenderWindow Game::window;

Game::Game() {
    Camera* camera = Camera::getInstance();
    window.create(sf::VideoMode(camera->getWindowWidth(), camera->getWindowHeight()), "Meat Boy");
    StateMgr::getInstance(); // Lazy initialization

    // font
    game_font.loadFromFile("resources/fonts/arial.ttf");
    text.setFont(game_font);

    loadLevel(); // for now load a level directly, then menu and then loadlevel
};

void Game::loadLevel() {
    World::getInstance()->addEntity(Player::getInstance());

    int tileSize = TILESIZE * SCALE;

    std::ifstream level;
    level.open("resources/levels/level-1.csv");

    std::string line;
    char delimiter = ',';

    std::string value;
    int column = 0; // top
    int row = 0; // left
    while (getline(level, line)) { /* read entire line into line */
        std::stringstream ss(line); /* create stringstream from line */
        while (getline(ss, value, delimiter)) { /* read each field from line */
            Vec2 pos(column * tileSize, row * tileSize);
            if (value == "0")
                World::getInstance()->addEntity(new Wall(pos));
            else if (value == "1") { // end
                World::getInstance()->addEntity(new LevelEnd(pos.x, pos.y));
            } else if (value == "2") { // player position
                Player::getInstance()->setInitialPosition(pos.x, pos.y);
            }
			column++;
        }
		row++;
		column = 0;
    }

	// set initial camera position
	Camera::getInstance()->setCameraCenter(row * tileSize);
}

void Game::run() {
    Stopwatch *stopwatch = Stopwatch::getInstance();
    while (window.isOpen()) {
        if (stopwatch->timeSinceLastUpdate() > TIME_PER_FRAME) {
            stopwatch->reset();
            process();
        }
        render();
    }
}

void Game::process() {
    if (StateMgr::getInstance()->isInMenuState()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed: {
                    handleMenuInput(event.key.code);
                }
                    break;
                default:
                    break;
            }
        }
    } else {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
                StateMgr::getInstance()->goToMenu();
        }
        Player::getInstance()->update();
    }
}

void Game::render() {
    window.clear();

    if (StateMgr::getInstance()->isInMenuState()) {
        // draw the game title
        text.setCharacterSize(48);
        text.setString("Meat Boy");
        text.setFillColor(sf::Color(100, 100, 100));
        text.setPosition(sf::Vector2f(10, 10));

		// reposition View (in case we came from the level)
		sf::View v = window.getView();
		v.setCenter(Camera::getInstance()->getWindowWidth() / 2.f, Camera::getInstance()->getWindowHeight() / 2.f);
		window.setView(v);

        window.draw(text);

        // draw levels
        for (int i = 1; i <= totalLevels; i++) {
            text.setString("Level " + std::to_string(i));
            text.setFillColor(i == selectedLevel ? sf::Color::White : sf::Color(100, 100, 100));
            text.setPosition(sf::Vector2f(120, 60 + (i * 80)));
            window.draw(text);
        }
    } else {
		float cameraDiff = Camera::getInstance()->getCameraCenter();
		sf::View v = window.getView();
		v.setCenter(Camera::getInstance()->getWindowWidth() / 2.f,  cameraDiff);
		window.setView(v);
        World::getInstance()->drawAll();
    }

    window.display();
}

void Game::handleMenuInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
        if (selectedLevel > 1) { selectedLevel--; }
        else { selectedLevel = 1; }
    } else if (key == sf::Keyboard::S || key == sf::Keyboard::Down) {
        if (selectedLevel < totalLevels) selectedLevel++;
    } else if (key == sf::Keyboard::Enter) {
        StateMgr::getInstance()->goToLevel(selectedLevel);
    }
}
