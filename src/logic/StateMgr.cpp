#include "StateMgr.h"

std::unique_ptr<StateMgr> StateMgr::stateMgr(new StateMgr);

StateMgr* StateMgr::getInstance() {
	return stateMgr.get();
}

void StateMgr::goToLevel() {
	currentState = LevelState;
}

void StateMgr::goToMenu() {
	currentState = MenuState;
}

bool StateMgr::isInMenuState() {
	return currentState == MenuState;
}

bool StateMgr::isInLevelState() {
	return currentState == LevelState;
}
