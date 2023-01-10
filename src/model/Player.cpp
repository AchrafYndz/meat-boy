#include "Player.h"
#include "Camera.h"

Model::Player::Player(floatVector2 pos) : Entity(Type::player) { position = pos; }

void Model::Player::buttonAction(KeyEnum key, bool pressed) {
    switch (key) {
    case Player::left:
        keys.left = pressed;
        break;
    case Player::right:
        keys.right = pressed;
        break;
    case Player::space:
        keys.space = pressed;
        break;
    default:
        break;
    }
}

void Model::Player::processInput(const std::shared_ptr<Camera>& camera) {
    floatVector2 playerPosition = camera->toPixels(getPosition()); // top left corner
    float currentX = playerPosition.x;

    if (keys.left) {
        if (jumpType == JumpType::toTheRight)
            currentAcceleration -= acceleration / 3.f;
        else
            currentAcceleration -= acceleration;
        facingLeft = true;
    } else if (keys.right) {
        if (jumpType == JumpType::toTheLeft)
            currentAcceleration += acceleration / 3.f;
        else
            currentAcceleration += acceleration;
        facingLeft = false;
    } else if (currentJumpingTime <= 0.f) { // deceleration if not jumping
        if (currentAcceleration < 0.34f && currentAcceleration > -0.34f)
            currentAcceleration = 0.f; // correction
        if (currentAcceleration > 0.f)
            currentAcceleration -= acceleration;
        else if (currentAcceleration < 0.f)
            currentAcceleration += acceleration;
    }

    if (currentAcceleration > topSpeed)
        currentAcceleration = topSpeed;
    else if (currentAcceleration < -topSpeed)
        currentAcceleration = -topSpeed;

    if (jumpAvailable && keys.space && state != State::inAir) {
        jumpAvailable = false;
        if (state == State::standingOnTile)
            jumpType = JumpType::normal;
        else if (state == State::onLeftWall) {
            jumpType = JumpType::toTheRight;
            currentAcceleration = topSpeed;
            facingLeft = false;
        } else {
            jumpType = JumpType::toTheLeft;
            currentAcceleration = -topSpeed;
            facingLeft = true;
        }

        currentJumpingTime = jumpingTotalTime;
    } else if (!keys.space)
        jumpAvailable = true;

    position = camera->normalizePosition(floatVector2(currentX + currentAcceleration, playerPosition.y));
}

void Model::Player::update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Camera> camera) {
    processInput(camera);

    floatVector2 playerPosition = camera->toPixels(getPosition()); // top left corner

    if (currentJumpingTime > 0) {
        playerPosition.y -= topSpeed;

        // if one third of the jump -> deceleration
        if (currentJumpingTime < jumpingTotalTime / 3.f)
            playerPosition.y += jumpDeceleration;

        currentJumpingTime -= TIME_PER_FRAME;
    } else
        playerPosition.y += topSpeed; // apply gravity

    /// collision

    // update sensor positions:
    float sensorOffset = 4.f;
    floatVector2 bounds(TILE_SIZE, TILE_SIZE);
    leftSensor.x = playerPosition.x - sensorOffset;
    leftSensor.y = playerPosition.y + (SCALE * bounds.y / 4.f);
    leftSensor.active = false;
    rightSensor.x = playerPosition.x + (SCALE * bounds.x) + sensorOffset;
    rightSensor.y = playerPosition.y + (SCALE * bounds.y / 4.f);
    rightSensor.active = false;
    bottomSensor.x = playerPosition.x + (SCALE * bounds.x / 2.f);
    bottomSensor.y = playerPosition.y + (SCALE * bounds.y) + sensorOffset;
    bottomSensor.active = false;

    floatRectangle rectangle{};
    for (const auto& entity : world->getEntities()) {
        if (entity->getType() == Type::wall) {
            floatVector2 entityPosition = camera->toPixels(entity->getPosition()); // top left corner

            rectangle.left = entityPosition.x;
            rectangle.top = entityPosition.y;
            rectangle.height = TILE_SIZE * SCALE;
            rectangle.width = TILE_SIZE * SCALE;

            if (world->rectangleContains(rectangle, floatVector2(bottomSensor.x, bottomSensor.y)))
                bottomSensor.active = true;
            else if (world->rectangleContains(rectangle, floatVector2(leftSensor.x, leftSensor.y)))
                leftSensor.active = true;
            else if (world->rectangleContains(rectangle, floatVector2(rightSensor.x, rightSensor.y)))
                rightSensor.active = true;
        }
    }
    if (bottomSensor.active)
        state = State::standingOnTile;
    else if (leftSensor.active)
        state = State::onLeftWall;
    else if (rightSensor.active)
        state = State::onRightWall;
    else
        state = State::inAir;

    for (const auto& entity : world->getEntities()) {
        // player with wall
        if (entity->getType() == Type::wall) {
            floatVector2 playerOverlap = world->getOverlap(playerPosition, camera->toPixels(entity->getPosition()));
            if (playerOverlap.x > 0.f && playerOverlap.y > 0.f) {
                if (playerOverlap.y < playerOverlap.x) { // compensate only the shortest overlap, in this case y
                    if (bottomSensor.active) {     // player on top of tile
                        playerPosition.y -= playerOverlap.y;
                    } else { // player hit tile from below
                        playerPosition.y += playerOverlap.y;
                    }
                } else {                      // compensate only x
                    if (rightSensor.active) { // player colliding on right wall
                        playerPosition.x -= playerOverlap.x;
                    } else if (leftSensor.active) { // player colliding on left wall
                        playerPosition.x += playerOverlap.x;
                    }
                }
            }
        }
        // player with goal (bandage girl)
        else if (entity->getType() == Type::goal) {
            floatVector2 playerOverlap = world->getOverlap(playerPosition, camera->toPixels(entity->getPosition()));
            if (playerOverlap.x > 0.f && playerOverlap.y > 0.f)
                reachedGoal = true;
        }
    }

    notifyObservers(playerPosition.x, playerPosition.y, camera, facingLeft);
    position = camera->normalizePosition(floatVector2(playerPosition.x, playerPosition.y));
}
