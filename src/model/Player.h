#ifndef INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H
#define INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H

#include "Camera.h"
#include "Entity.h"
#include "ObserverPattern.h"

#include <memory>

namespace Model {
struct Vec2;

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

    enum PlyState { standingOnTile, onAir, onLeftWall, onRightWall };
    PlyState state = PlyState::onAir;

    const float speedMultiplier = WINDOW_WIDTH / 480.f;
    const float acceleration = 60.f * TIME_PER_FRAME * speedMultiplier;
    float currentAcceleration = 0.f;
    const float topSpeed = 300.f * TIME_PER_FRAME * speedMultiplier;

    const float JUMPING_TOTAL_TIME = 0.8f;
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
    explicit Player(Vec2 pos);

    enum KeyEnum { left, right, space };

    void buttonAction(KeyEnum k, bool pressed);

    void processInput(const std::shared_ptr<Camera>& camera);

    void update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Model::Camera> camera) override;

    [[nodiscard]] bool hasReachedGoal() const { return reachedGoal; }
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H