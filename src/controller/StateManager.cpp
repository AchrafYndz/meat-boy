#include "StateManager.h"

// This method changes the current level to the specified level, with the
// specified auto-scrolling setting.
void StateManager::goToLevel(int level, bool autoScrolling) {
    currentLevel.current = level;
    currentLevel.autoscroll = autoScrolling;
}

// This method changes the current level to the menu state.
void StateManager::goToMenu() { currentLevel.current = 0; }

// This method returns `true` if the application is in the menu state,
// and `false` otherwise.
bool StateManager::isInMenuState() { return currentLevel.current == 0; }

// This method returns `true` if the application is in a level state,
// and `false` otherwise.
bool StateManager::isInLevelState() { return currentLevel.current > 0; }
