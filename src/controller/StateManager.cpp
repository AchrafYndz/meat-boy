#include "StateManager.h"

std::shared_ptr<StateManager> StateManager::stateMgr(new StateManager);

std::shared_ptr<StateManager> StateManager::getInstance() { return stateMgr; }

void StateManager::goToLevel(int level, bool autoScrolling) {
	currentLevel.current = level;
	currentLevel.autoscroll = autoScrolling;
}

void StateManager::goToMenu() { currentLevel.current = 0; }

bool StateManager::isInMenuState() { return currentLevel.current == 0; }

bool StateManager::isInLevelState() { return currentLevel.current > 0; }
