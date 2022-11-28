#ifndef INC_2022_PROJECT_ACHRAFYNDZ_GAME_H
#define INC_2022_PROJECT_ACHRAFYNDZ_GAME_H

#include "../logic/Stopwatch.h"
#include <SFML/Graphics.hpp>

// CONSTANTS
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const float TIME_PER_FRAME = 1 / 60.0f;

class Game {
private:
    static sf::RenderWindow window;

public:
    // Constructor
    Game();

	// Load a Level
	void loadLevel();

    // Main game loop
    void run();

	static sf::RenderWindow* getWindow() { return &window; }
private:
    void process();

    // Clears the last frame and displays new updates
    void render();

	// Hanles inputs for menu
	void handleMenuInput(sf::Keyboard::Key key);
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_GAME_H
