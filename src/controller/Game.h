#ifndef INC_2022_PROJECT_ACHRAFYNDZ_GAME_H
#define INC_2022_PROJECT_ACHRAFYNDZ_GAME_H

#include "../model/Camera.h"
#include "../util/Stopwatch.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>

class Game {
private:
    static sf::RenderWindow window;

    std::shared_ptr<StateManager> stateManager;

    std::shared_ptr<Camera> camera;

    sf::Font game_font;
    sf::Text text;

	int selectedLevel = 1;
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
