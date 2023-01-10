#ifndef INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H
#define INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H

#include "../util/floatVector2.h"
#include "Camera.h"
#include "Entity.h"
#include "ObserverPattern.h"

#include <memory>

namespace Model {
class Player : public Entity, public Subject {
private:
    struct Sensor {
        float x;
        float y;
        bool active = false;
    };
    Sensor leftSensor;
    Sensor rightSensor;
    Sensor bottomSensor;

    enum State { standingOnTile, inAir, onLeftWall, onRightWall };
    State state = State::inAir;

    const float speedMultiplier = WINDOW_WIDTH / 480.f;
    const float acceleration = 60.f * TIME_PER_FRAME * speedMultiplier;
    float currentAcceleration = 0.f;
    const float topSpeed = 300.f * TIME_PER_FRAME * speedMultiplier;

    const float jumpingTotalTime = 0.8f;
    float currentJumpingTime = 0.f;
    const float jumpDeceleration = 120.f * TIME_PER_FRAME * speedMultiplier;

    bool jumpAvailable = true;

    enum JumpType { normal, toTheLeft, toTheRight };
    JumpType jumpType{};

    bool reachedGoal = false;

    bool facingLeft = false;

    struct Keys {
        bool left = false;
        bool right = false;
        bool space = false;
    };
    Keys keys;

public:
    explicit Player(floatVector2 pos);

    enum KeyEnum { left, right, space };

    void buttonAction(KeyEnum key, bool pressed);

    void processInput(const std::shared_ptr<Camera>& camera);

    void update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Model::Camera> camera) override;

    [[nodiscard]] bool hasReachedGoal() const { return reachedGoal; }
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H