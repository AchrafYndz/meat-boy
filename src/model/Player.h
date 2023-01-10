#ifndef INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H
#define INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H

#include "../util/floatVector2.h"
#include "Camera.h"
#include "Entity.h"
#include "ObserverPattern.h"

#include <memory>

namespace Model {
/**
 * The Player class represents the playable character in the game.
 * It inherits from the Entity base class and also implements the Subject interface for the observer pattern.
 */
class Player : public Entity, public Subject {
private:
    /**
     * Struct representing a sensor
     */
    struct Sensor {
        float x;
        float y;
        bool active = false;
    };
    Sensor leftSensor;
    Sensor rightSensor;
    Sensor bottomSensor;

    /**
     * Enum representing the collision state of the player
     */
    enum State { standingOnTile, inAir, onLeftWall, onRightWall };
    State state = State::inAir;

    /**
     * Variables used for player movement
     */
    const float speedMultiplier = WINDOW_WIDTH / 480.f;
    const float acceleration = 60.f * TIME_PER_FRAME * speedMultiplier;
    float currentAcceleration = 0.f;
    const float topSpeed = 300.f * TIME_PER_FRAME * speedMultiplier;

    const float jumpingTotalTime = 0.8f;
    float currentJumpingTime = 0.f;
    const float jumpDeceleration = 120.f * TIME_PER_FRAME * speedMultiplier;

    bool jumpAvailable = true;

    /**
     * Enum representing the type of jump
     */
    enum JumpType { normal, toTheLeft, toTheRight };
    JumpType jumpType{};

    /** Represents whether the player has reached the goal or not */
    bool reachedGoal = false;

    /** True if the player is facing left, otherwise false */
    bool facingLeft = false;

    /**
     * Struct representing the keys pressed
     */
    struct Keys {
        bool left = false;
        bool right = false;
        bool space = false;
    };
    Keys keys;

public:
    /**
     *  Constructor for creating a new player object
     *  @param position_ The initial position of the player
     */
    explicit Player(floatVector2 position_);

    /**
     *  Enumeration representing the keys
     */
    enum KeyEnum { left, right, space };

    /**
     *  Method to handle button actions (press or release)
     *  @param key The key which is pressed/released
     *  @param pressed Boolean indicating if the key is pressed or released
     */
    void buttonAction(KeyEnum key, bool pressed);

    /**
     *  Method to process input from the player
     *  @param camera A shared pointer to the camera
     */
    void processInput(const std::shared_ptr<Camera>& camera);

    /**
     *  Update method which updates the player's state and position
     *  @param world A shared pointer to the game's world
     *  @param camera A shared pointer to the camera
     */
    void update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Model::Camera> camera) override;

    /**
     *  Method to check if the player has reached the goal
     *  @return Boolean value indicating if the goal has been reached or not
     */
    [[nodiscard]] bool hasReachedGoal() const { return reachedGoal; }
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H