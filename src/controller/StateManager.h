#ifndef INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H
#define INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H

#include <memory>

// This class manages the current state of the application.
// It has methods for changing to different levels and the menu,
// as well as methods for checking the current state.
class StateManager {
private:

    // This struct contains information about the current level.
    struct Level {
        // The `current` variable is the number of the current level.
        // If `current` is 0, the application is in the menu state.
        // If `current` is -1, there is no current level.
        int current = -1;

        // The `autoscroll` variable indicates whether the current level
        // has auto-scrolling enabled.
        bool autoscroll;
    };

    // An instance of the `Level` struct, which contains information
    // about the current level.
    Level currentLevel;

public:
    // This is the constructor
    StateManager() = default;
    // This method changes the current level to the specified level,
    // with the specified auto-scrolling setting.
    void goToLevel(int level, bool autoScrolling);

    // This method changes the current level to the menu state.
    void goToMenu();

    // This method returns `true` if the application is in the menu state,
    // and `false` otherwise.
    bool isInMenuState();

    // This method returns `true` if the application is in a level state,
    // and `false` otherwise.
    bool isInLevelState();

    // This method returns the number of the current level.
    int getCurrentLevel() const { return currentLevel.current; }

    // This method returns `true` if the current level has auto-scrolling
    // enabled, and `false` otherwise.
    bool currentLevelHasAutoScroll() { return currentLevel.autoscroll; }
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H