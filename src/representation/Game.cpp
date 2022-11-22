#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Meat Boy") {};

void Game::run() {
    Stopwatch* stopwatch = Stopwatch::getInstance();
    while (window.isOpen()) {
        if (stopwatch->timeSinceLastUpdate() > TIME_PER_FRAME) {
            stopwatch->reset();
            processEvents();
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code);
                break;
            default:
                break;
        }
    }
}

void Game::render() {
    window.clear();
    window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::W || key == sf::Keyboard::Space)
        std::cout << "Player tried to jump!" << std::endl;
    else if (key == sf::Keyboard::A)
        std::cout << "Player tried to move left!" << std::endl;
    else if (key == sf::Keyboard::D)
        std::cout << "Player tried to move right!" << std::endl;
}
