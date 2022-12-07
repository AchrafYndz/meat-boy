#ifndef INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H
#define INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H

#include <memory>

class StateManager {
private:
    StateManager() {};
    static std::unique_ptr<StateManager> stateMgr;

    // 0 = menu, 1.. = levels
    int currentLevel = -1;
public:
    StateManager(StateManager &other) = delete;

    void operator=(const StateManager &other) = delete;

    static StateManager *getInstance();

    void goToLevel(int level);

    void goToMenu();

    bool isInMenuState();

    bool isInLevelState();

    int getCurrentLevel() const { return currentLevel; }
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_STATEMANAGER_H