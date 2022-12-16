#ifndef INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H
#define INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

#include <memory>

struct Vec2;

class Player : public Entity {
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

    const float acceleration = 1.f;
    float currentAcceleration = 0.f;
    const float topSpeed = 5.f;

    const float JUMPING_TOTAL_TIME = 0.8f;
    float currentJumpingTime = 0.f;
    const float jumpDeceleration = 2.f;

    bool jumpAvailable = true;

    enum JumpType { normal, toTheLeft, toTheRight };
    JumpType jumpType;

    bool reachedGoal = false;

public:
    Player(Vec2 pos);

    void processInput();

    void update();

	void draw() override;

    void startLevel(Vec2 pos);

    bool hasReachedGoal() { return reachedGoal; }
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H