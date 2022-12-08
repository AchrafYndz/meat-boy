#ifndef INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H
#define INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H

#include <memory>

class StateManager {
private:
    StateManager(){};
    static std::unique_ptr<StateManager> stateMgr;
	
	struct Level {
		// 0 = menu, 1.. = levels
		int current = -1;
		bool autoscroll;
	};
	Level currentLevel;

public:
    StateManager(StateManager& other) = delete;

    void operator=(const StateManager& other) = delete;

    static StateManager* getInstance();

    void goToLevel(int level, bool autoScrolling);

    void goToMenu();

    bool isInMenuState();

    bool isInLevelState();

    int getCurrentLevel() const { return currentLevel.current; }

	bool currentLevelHasAutoScroll() { return currentLevel.autoscroll; }
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H