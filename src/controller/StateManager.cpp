#include "StateManager.h"

// This method changes the current level to the specified level, with the
// specified auto-scrolling setting.
void Controller::StateManager::goToLevel(int level, bool autoScrolling) {
    currentLevel.state = level;
    currentLevel.autoscroll = autoScrolling;
}

// This method changes the current level to the menu state.
void Controller::StateManager::goToMenu() { currentLevel.state = 0; }

