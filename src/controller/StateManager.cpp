#include "StateManager.h"

// This method changes the current level to the specified level, with the
// specified auto-scrolling setting.
void Controller::StateManager::goToLevel(int level, bool autoScrolling) {
    currentLevel.current = level;
    currentLevel.autoscroll = autoScrolling;
}

// This method changes the current level to the menu state.
void Controller::StateManager::goToMenu() { currentLevel.current = 0; }

// This method returns `true` if the application is in the menu state,
// and `false` otherwise.
bool Controller::StateManager::isInMenuState() const { return currentLevel.current == 0; }
