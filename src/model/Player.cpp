#include "Player.h"
#include "Camera.h"

Model::Player::Player(Vec2 pos) : Entity(Type::player) { position = pos; }

void Model::Player::buttonAction(KeyEnum k, bool pressed) {
    switch (k) {
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
    Vec2 plyPos = camera->toPixels(getPosition()); // top left corner
    float currentX = plyPos.x;

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

    if (jumpAvailable && keys.space && state != PlyState::onAir) {
        jumpAvailable = false;
        if (state == PlyState::standingOnTile)
            jumpType = JumpType::normal;
        else if (state == PlyState::onLeftWall) {
            jumpType = JumpType::toTheRight;
            currentAcceleration = topSpeed;
            facingLeft = false;
        } else {
            jumpType = JumpType::toTheLeft;
            currentAcceleration = -topSpeed;
            facingLeft = true;
        }

        currentJumpingTime = JUMPING_TOTAL_TIME;
    } else if (!keys.space)
        jumpAvailable = true;

    position = camera->normalizedPosition(Vec2(currentX + currentAcceleration, plyPos.y));
}

void Model::Player::update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Camera> camera) {
    processInput(camera);

    Vec2 plyPos = camera->toPixels(getPosition()); // top left corner

    if (currentJumpingTime > 0) {
        plyPos.y -= topSpeed;

        // if one third of the jump -> deceleration
        if (currentJumpingTime < JUMPING_TOTAL_TIME / 3.f)
            plyPos.y += jumpDeceleration;

        currentJumpingTime -= TIME_PER_FRAME;
    } else
        plyPos.y += topSpeed; // apply gravity

    /// collision

    // update sensor positions:
    float sensorOffset = 4.f;
    Vec2 bounds(TILE_SIZE, TILE_SIZE);
    leftSensor.x = plyPos.x - sensorOffset;
    leftSensor.y = plyPos.y + (SCALE * bounds.y / 4.f);
    leftSensor.active = false;
    rightSensor.x = plyPos.x + (SCALE * bounds.x) + sensorOffset;
    rightSensor.y = plyPos.y + (SCALE * bounds.y / 4.f);
    rightSensor.active = false;
    bottomSensor.x = plyPos.x + (SCALE * bounds.x / 2.f);
    bottomSensor.y = plyPos.y + (SCALE * bounds.y) + sensorOffset;
    bottomSensor.active = false;

    World::floatRect r{};
    for (const auto& entity : world->getEntities()) {
        if (entity->getType() == Type::wall) {
            Vec2 ePos = camera->toPixels(entity->getPosition()); // top left corner

            r.left = ePos.x;
            r.top = ePos.y;
            r.height = TILE_SIZE * SCALE;
            r.width = TILE_SIZE * SCALE;

            if (world->rectContainsPoint(r, Vec2(bottomSensor.x, bottomSensor.y)))
                bottomSensor.active = true;
            else if (world->rectContainsPoint(r, Vec2(leftSensor.x, leftSensor.y)))
                leftSensor.active = true;
            else if (world->rectContainsPoint(r, Vec2(rightSensor.x, rightSensor.y)))
                rightSensor.active = true;
        }
    }
    if (bottomSensor.active)
        state = PlyState::standingOnTile;
    else if (leftSensor.active)
        state = PlyState::onLeftWall;
    else if (rightSensor.active)
        state = PlyState::onRightWall;
    else
        state = PlyState::onAir;

    for (const auto& entity : world->getEntities()) {
        // player with wall
        if (entity->getType() == Type::wall) {
            Vec2 overlapPly = world->getOverlap(plyPos, camera->toPixels(entity->getPosition()));
            bool thereIsCollision = overlapPly.x > 0.f && overlapPly.y > 0.f;

            if (thereIsCollision) {
                if (overlapPly.y < overlapPly.x) { // compensate only the shortest overlap, in this case y
                    if (bottomSensor.active) {     // player on top of tile
                        plyPos.y -= overlapPly.y;
                    } else { // player hit tile from below
                        plyPos.y += overlapPly.y;
                    }
                } else {                      // compensate only x
                    if (rightSensor.active) { // player colliding on right wall
                        plyPos.x -= overlapPly.x;
                    } else if (leftSensor.active) { // player colliding on left wall
                        plyPos.x += overlapPly.x;
                    }
                }
            }
        }
        // player with goal (bandage girl)
        else if (entity->getType() == Type::goal) {
            Vec2 overlapPly = world->getOverlap(plyPos, camera->toPixels(entity->getPosition()));
            bool thereIsCollision = overlapPly.x > 0.f && overlapPly.y > 0.f;
            if (thereIsCollision)
                reachedGoal = true;
        }
    }

    notifyObservers(plyPos.x, plyPos.y, camera, facingLeft);
    position = camera->normalizedPosition(Vec2(plyPos.x, plyPos.y));
}
