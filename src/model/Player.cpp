#include "Player.h"
#include "Camera.h"
#include "../view/EntityView.h"

#include <iostream>


Player::Player(Vec2 pos) : Entity(Type::player) {
    position = pos;
}

void Player::buttonAction(KeyEnum k, bool pressed)
{
	switch (k)
	{
	case Player::left: keys.left = pressed; break;
	case Player::right: keys.right = pressed; break;
	case Player::space: keys.space = pressed; break;
	default:
		break;
	}
}

void Player::processInput() {
	Vec2 plyPos = Camera::getInstance()->toPixels(getPosition()); // top left corner
    int currentX = plyPos.x;

    if (keys.left) {
        if (jumpType == JumpType::toTheRight)
            currentAcceleration -= acceleration / 3.f;
        else
            currentAcceleration -= acceleration;
		entView->face(true);
    } else if (keys.right) {
        if (jumpType == JumpType::toTheLeft)
            currentAcceleration += acceleration / 3.f;
        else
            currentAcceleration += acceleration;
		entView->face(false);
    } else if (currentJumpingTime <= 0.f) { // deceleration if not jumping
		if (currentAcceleration < 0.2f && currentAcceleration > -0.2f) currentAcceleration = 0.f; // correction
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
        } else if (state == PlyState::onRightWall) {
            jumpType = JumpType::toTheLeft;
            currentAcceleration = -topSpeed;
        }

        currentJumpingTime = JUMPING_TOTAL_TIME;
    } else if (!keys.space)
        jumpAvailable = true;

	notifyObservers(plyPos.x, plyPos.y);
	position = Camera::getInstance()->normalizedPosition(Vec2(currentX + currentAcceleration, plyPos.y));

	std::cout << std::to_string(currentAcceleration) << "\n";
}

void Player::update() {
	processInput();

	Vec2 plyPos = Camera::getInstance()->toPixels(getPosition()); // top left corner

	int currentY = plyPos.y;
	if (currentJumpingTime > 0) {
		if (jumpType == JumpType::normal || jumpType == JumpType::toTheLeft || jumpType == JumpType::toTheRight)
			plyPos.y -= topSpeed;

		// if one third of the jump -> deceleration
		if (currentJumpingTime < JUMPING_TOTAL_TIME / 3.f) plyPos.y += jumpDeceleration;

		currentJumpingTime -= TIME_PER_FRAME;

	}
	else  plyPos.y += topSpeed; // apply gravity

	/// collision

	// update sensor positions:
	float sensorOffset = 4.f;
	Vec2 bounds = entView->size();
	leftSensor.x = plyPos.x - sensorOffset;
	leftSensor.y = plyPos.y + (SCALE * bounds.y / 4.f);
	leftSensor.active = false;
	rightSensor.x = plyPos.x + (SCALE * bounds.x) + sensorOffset;
	rightSensor.y = plyPos.y + (SCALE * bounds.y / 4.f);
	rightSensor.active = false;
	bottomSensor.x = plyPos.x + (SCALE * bounds.x / 2.f);
	bottomSensor.y = plyPos.y + (SCALE * bounds.y) + sensorOffset;
	bottomSensor.active = false;

	Vec2 ePos;
	World::floatRect r;
	for (auto e : World::getInstance()->getEntities()) {
		if (e->getType() == Type::wall) {
			Vec2 ePos = Camera::getInstance()->toPixels(e->getPosition()); // top left corner

			r.left = ePos.x;
			r.top = ePos.y;
			r.height = TILESIZE * SCALE;
			r.width = TILESIZE * SCALE;

			if (World::getInstance()->rectContainsPoint(r, Vec2(bottomSensor.x, bottomSensor.y)))
				bottomSensor.active = true;
			else if (World::getInstance()->rectContainsPoint(r, Vec2(leftSensor.x, leftSensor.y)))
				leftSensor.active = true;
			else if (World::getInstance()->rectContainsPoint(r, Vec2(rightSensor.x, rightSensor.y)))
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

	for (auto e : World::getInstance()->getEntities()) {
		// player with wall
		if (e->getType() == Type::wall) {
			Vec2 overlapPly = World::getInstance()->getOverlap(plyPos, Camera::getInstance()->toPixels(e->getPosition()));
			bool thereIsCollision = overlapPly.x > 0.f && overlapPly.y > 0.f;

			if (thereIsCollision) {
				if (overlapPly.y < overlapPly.x) { // compensate only the shortest overlap, in this case y
					if (bottomSensor.active) {     // player on top of tile
						plyPos.y -= overlapPly.y;
					}
					else { // player hit tile from below
						plyPos.y += overlapPly.y;
					}
				}
				else { // compensate only x
					if (rightSensor.active) { // player colliding on right wall
						plyPos.x -= overlapPly.x;
					}
					else if (leftSensor.active) { // player colliding on left wall
						plyPos.x += overlapPly.x;
					}
				}

			}
		}
		// player with goal (bandage girl)
		else if (e->getType() == Type::goal) {
			Vec2 overlapPly = World::getInstance()->getOverlap(plyPos, Camera::getInstance()->toPixels(e->getPosition()));
			bool thereIsCollision = overlapPly.x > 0.f && overlapPly.y > 0.f;
			if (thereIsCollision)
				reachedGoal = true;
		}
	}

	notifyObservers(plyPos.x, plyPos.y);
	position = Camera::getInstance()->normalizedPosition(Vec2(plyPos.x, plyPos.y));
}

void Player::draw() {
    Vec2 pos = Camera::getInstance()->toPixels(position);

	entView->draw(pos);
}

void Player::startLevel(Vec2 pos) {
    reachedGoal = false;
    position = pos;
}