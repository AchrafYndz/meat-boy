#include "StateManager.h"

std::unique_ptr<StateManager> StateManager::stateMgr(new StateManager);

StateManager *StateManager::getInstance() {
    return stateMgr.get();
}

void StateManager::goToLevel(int level) {
    currentLevel = level;
}

void StateManager::goToMenu() {
    currentLevel = 0;
}

bool StateManager::isInMenuState() {
    return currentLevel == 0;
}

bool StateManager::isInLevelState() {
    return currentLevel > 0;
}
