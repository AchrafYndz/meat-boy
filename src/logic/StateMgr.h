#ifndef INC_2022_PROJECT_ACHRAFYNDZ_STATEMGR_H
#define INC_2022_PROJECT_ACHRAFYNDZ_STATEMGR_H

#include <memory>

class StateMgr {
private:
    StateMgr() { currentState = MenuState; };
    static std::unique_ptr<StateMgr> stateMgr;

    enum state {
        MenuState, LevelState
    };
    state currentState;

public:
    StateMgr(StateMgr &other) = delete;

    void operator=(const StateMgr &other) = delete;

    static StateMgr *getInstance();

    void goToLevel(int level);

    void goToMenu();

    bool isInMenuState();

    bool isInLevelState();
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_STATEMGR_H