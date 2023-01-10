#ifndef INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H
#define INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H

#include <memory>

namespace Controller {

/**
 *  StateManager is a class that handles the different states of the game, namely the level states and menu states
 */
class StateManager {
private:
    /**
     *  This struct contains information about the current level.
     */
    struct Level {
        /** The `state` variable is the number of the current level.
         * If `state` is 0, the application is in the menu state.
         */
        int state = 0;

        /**
         *  The `autoscroll` variable indicates whether the current level
         *  has auto-scrolling enabled.
         */
        bool autoscroll;
    };

    /**
     * An instance of the `Level` struct, which contains information
     * about the current level.
     */
    Level currentLevel;

public:
    /**
     *  Default constructor for the StateManager class
     */
    StateManager() = default;

    /**
     *  This method changes the current level to the specified level,
     *  with the specified auto-scrolling setting.
     *
     *  @param level The level number to change to
     *  @param autoScrolling Whether auto-scrolling is enabled on the level or not
     */
    void goToLevel(int level, bool autoScrolling);

    /**
     *  This method changes the current level to the menu state.
     */
    void goToMenu();

    /**
     *  This method returns `true` if the application is in the menu state,
     *  and `false` otherwise.
     *
     *  @return True if in menu state, false otherwise
     */
    [[nodiscard]] bool isInMenuState() const { return currentLevel.state == 0; };

    /**
     *  This method returns `true` if the current level has auto-scrolling
     *  enabled, and `false` otherwise.
     *
     *  @return true if auto-scrolling is enabled, false otherwise
     */
    [[nodiscard]] bool currentLevelHasAutoScroll() const { return currentLevel.autoscroll; }
};
} // namespace Controller

#endif // INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H
