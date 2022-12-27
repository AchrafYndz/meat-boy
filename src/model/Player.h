#ifndef INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H
#define INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H

#include "ObserverPattern.h"
#include "Entity.h"

#include <memory>

struct Vec2;

class Player : public Entity, public Subject {
private:
    struct Sensor {
        int x;
        int y;
        bool active = false;
    };
    Sensor leftSensor;
    Sensor rightSensor;
    Sensor bottomSensor;

    enum PlyState { none, standingOnTile, onAir, onLeftWall, onRightWall };
    PlyState state = PlyState::onAir;

    const float acceleration = 60.f * TIME_PER_FRAME;
    float currentAcceleration = 0.f;
    const float topSpeed = 300.f * TIME_PER_FRAME;

    const float JUMPING_TOTAL_TIME = 0.8f;
    float currentJumpingTime = 0.f;
	const float jumpDeceleration = 120.f * TIME_PER_FRAME;

    bool jumpAvailable = true;

    enum JumpType { normal, toTheLeft, toTheRight };
    JumpType jumpType;

    bool reachedGoal = false;

    bool facingLeft = false;

    struct Keys {
        bool left = false;
        bool right = false;
        bool space = false;
    };
    Keys keys;

public:
    Player(Vec2 pos);

    enum KeyEnum { left, right, space };

    void buttonAction(KeyEnum k, bool pressed);

    void processInput();

    void update() override;

    bool hasReachedGoal() { return reachedGoal; }
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H