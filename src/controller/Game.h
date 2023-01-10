#ifndef INC_2022_PROJECT_ACHRAFYNDZ_GAME_H
#define INC_2022_PROJECT_ACHRAFYNDZ_GAME_H

#include "../model/Camera.h"
#include "../util/Stopwatch.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>

namespace Controller {

/**
 *  Game class is the main class that controls the game loop, input handling and rendering.
 *  It controls the game state through the StateManager and renders the game through the SFML library
 */
class Game {
private:
    /** The SFML window that is used to render the game */
    static sf::RenderWindow window;

    /** A shared pointer to the state manager that controls the game state */
    std::shared_ptr<StateManager> stateManager;

    /** A shared pointer to the camera that controls the view of the game world */
    std::shared_ptr<Model::Camera> camera;

    /** A shared pointer to the game world that contains all the entities */
    std::shared_ptr<Model::World> world;

    /** The SFML font used to render the text in the game */
    sf::Font gameFont;

    /** The SFML text object that is used to render the text in the game */
    sf::Text text;

    /** The currently selected level of the game */
    int selectedLevel = 1;

    /** The total number of levels in the game */
    int totalLevels = 3;

public:
    /**
     *  Constructor for the Game class
     */
    Game();

    /**
     *  Main game loop that updates, processes, and renders the game
     */
    void run();

    /**
     *  Returns a pointer to the SFML window used to render the game
     *
     *  @return A pointer to the SFML window
     */
    static sf::RenderWindow* getWindow() { return &window; }

private:
    /**
     *  Function that processes all the game logic
     */
    void process();

    /**
     *  Function that's responsible for displaying new updates
     */
    void render();

    /**
     *  Handles input for the main menu
     *  @param key key pressed
     */
    void handleMenuInput(sf::Keyboard::Key key);
};
} // namespace Controller

#endif // INC_2022_PROJECT_ACHRAFYNDZ_GAME_H