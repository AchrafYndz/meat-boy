#ifndef INC_2022_PROJECT_ACHRAFYNDZ_GAME_H
#define INC_2022_PROJECT_ACHRAFYNDZ_GAME_H

#include "Game.h"

#include "../logic/Stopwatch.h"
#include <SFML/Graphics.hpp>

// CONSTANTS
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const double TIME_PER_FRAME = 1 / 60.0;

class Game {
private:
    sf::RenderWindow window;

public:
    // Constructor
    Game();
    // Main game loop
    void run();

private:
    // Handles SFML events
    void processEvents();
    // Clears the last frame and displays new updates
    void render();
    // Hanles keyboard inputs
    void handlePlayerInput(sf::Keyboard::Key key);
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_GAME_H
