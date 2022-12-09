#ifndef INC_2022_PROJECT_ACHRAFYNDZ_GAME_H
#define INC_2022_PROJECT_ACHRAFYNDZ_GAME_H

#include "../util/Stopwatch.h"
#include <SFML/Graphics.hpp>

// CONSTANTS
const double TIME_PER_FRAME = 1 / 60.0;

class Game {
private:
    static sf::RenderWindow window;

    sf::Font game_font;
    sf::Text text;

	int selectedLevel = 0;
	int totalLevels = 3;

public:
    // Constructor
    Game();

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
