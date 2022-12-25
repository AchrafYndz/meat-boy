#ifndef INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H
#define INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H

#include "Entity.h"
#include "ObserverPattern.h"

#include <memory>

struct Vec2;

struct floatRect {
    float left = 0.0f;
    float top = 0.0f;
    float height = 0.0f;
    float width = 0.0f;

    bool contains(float x, float y) const {
        float minX = std::min(left, left + width);
        float maxX = std::max(left, left + width);
        float minY = std::min(top, top + height);
        float maxY = std::max(top, top + height);

        return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
    }
};

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

    void draw() override;

    void startLevel(Vec2 pos);

    bool hasReachedGoal() { return reachedGoal; }
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H