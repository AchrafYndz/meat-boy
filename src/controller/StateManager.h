#ifndef INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H
#define INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H

#include <memory>

namespace Controller {
class StateManager {
private:
    // This struct contains information about the current level.
    struct Level {
        // The `current` variable is the number of the current level.
        // If `current` is 0, the application is in the menu state.
        int current = 0;

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
    [[nodiscard]] bool isInMenuState() const;

    // This method returns `true` if the current level has auto-scrolling
    // enabled, and `false` otherwise.
    [[nodiscard]] bool currentLevelHasAutoScroll() const { return currentLevel.autoscroll; }
};
} // namespace Controller

#endif // INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H