#include "Game.h"
#include "../model/Camera.h"
#include "../model/Player.h"
#include "StateManager.h"

#include <fstream>
#include <sstream>

sf::RenderWindow Game::window;

Game::Game() {
	std::shared_ptr<Camera> camera = Camera::getInstance();
    window.create(sf::VideoMode(camera->getWindowWidth(), camera->getWindowHeight()), "Meat Boy");

    game_font.loadFromFile("resources/fonts/arial.ttf");
    text.setFont(game_font);

    StateManager::getInstance()->goToMenu();
};

void Game::run() {
	std::shared_ptr<Stopwatch> stopwatch = Stopwatch::getInstance();
    while (window.isOpen()) {
        if (stopwatch->timeSinceLastUpdate() > TIME_PER_FRAME) {
            stopwatch->reset();
            process();
        }
        render();
    }
}

void Game::process() {
    if (StateManager::getInstance()->isInMenuState()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

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
    } else {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
                StateManager::getInstance()->goToMenu();
        }
        Player::getInstance()->update();
        // WIN STATE -> go to Next Level or Main Menu if it's the last level
        if (Player::getInstance()->hasReachedGoal()) {
            if (selectedLevel == 3)
                StateManager::getInstance()->goToMenu();
            else {
				selectedLevel++;
                World::getInstance()->loadLevel(selectedLevel);
            }
        }
        // DIE -> Restart Level
        if (!Camera::getInstance()->entityIsVisible(Player::getInstance())) {
			World::getInstance()->loadLevel(selectedLevel);
        }
    }
}

void Game::render() {
    window.clear();

    if (StateManager::getInstance()->isInMenuState()) {
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

        // draw level selection
        for (int i = 1; i <= totalLevels; i++) {
            text.setString("Level " + std::to_string(i));
            text.setFillColor(i == selectedLevel ? sf::Color::White : sf::Color(100, 100, 100));
            text.setPosition(sf::Vector2f(120, 60 + (i * 80)));
            window.draw(text);
        }
    } else {
        float cameraDiff = Camera::getInstance()->getCameraCenter();
        sf::View v = window.getView();
        v.setCenter(Camera::getInstance()->getWindowWidth() / 2.f, cameraDiff);
        window.setView(v);
        World::getInstance()->draw();
    }

    window.display();
}

void Game::handleMenuInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
        if (selectedLevel > 1) {
            selectedLevel--;
        } else {
            selectedLevel = 1;
        }
    } else if (key == sf::Keyboard::S || key == sf::Keyboard::Down) {
        if (selectedLevel < totalLevels)
            selectedLevel++;
    } else if (key == sf::Keyboard::Enter)
		World::getInstance()->loadLevel(selectedLevel);
}
