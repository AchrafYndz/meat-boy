#include "Player.h"
#include "../controller/Game.h"

#include <iostream>

std::unique_ptr<Player> Player::player(new Player);

Player *Player::getInstance() {
    return player.get();
}

Player::Player() : Entity(Type::player) {
    texture.loadFromFile("resources/sprites/player-sprite.png");

    sprite.setTexture(texture);
    sprite.setScale(SCALE, SCALE);
}

void Player::processInput() {
    int currentX = sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (jumpType == JumpType::toTheRight)
            currentAcceleration -= acceleration / 3.f;
        else currentAcceleration -= acceleration;
        sprite.setScale(-SCALE, SCALE);
        sprite.setOrigin(sprite.getLocalBounds().width, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (jumpType == JumpType::toTheLeft)
			currentAcceleration += acceleration / 3.f;
		else currentAcceleration += acceleration;
		sprite.setScale(SCALE, SCALE);
		sprite.setOrigin(0.f, 0.f);
	}
	else if (currentJumpingTime < 0.f) { // deceleration if not jumping
		if (currentAcceleration > 0.f) currentAcceleration -= acceleration;
		else if (currentAcceleration < 0.f) currentAcceleration += acceleration;
	}

    if (currentAcceleration > topSpeed) currentAcceleration = topSpeed;
    else if (currentAcceleration < -topSpeed) currentAcceleration = -topSpeed;

    if (jumpAvailable && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && state != PlyState::onAir) {
        jumpAvailable = false;
        if (state == PlyState::standingOnTile) jumpType = JumpType::normal;
        else if (state == PlyState::onLeftWall) {
            jumpType = JumpType::toTheRight;
            currentAcceleration = topSpeed;
        } else if (state == PlyState::onRightWall) {
            jumpType = JumpType::toTheLeft;
            currentAcceleration = -topSpeed;
        }

        currentJumpingTime = JUMPING_TOTAL_TIME;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) jumpAvailable = true;

    sprite.setPosition(currentX + currentAcceleration, sprite.getPosition().y);
}

void Player::update() {
    processInput();

    int currentY = sprite.getPosition().y;
    if (currentJumpingTime > 0) {
        if (jumpType == JumpType::normal || jumpType == JumpType::toTheLeft || jumpType == JumpType::toTheRight)
            sprite.setPosition(sprite.getPosition().x, currentY - topSpeed);

        // if one third of the jump -> deceleration
        if (currentJumpingTime < JUMPING_TOTAL_TIME / 3.f) {
            sprite.setPosition(sprite.getPosition().x, currentY + jumpDeceleration);
        }

        currentJumpingTime -= TIME_PER_FRAME;
    } else { // apply gravity
        sprite.setPosition(sprite.getPosition().x, currentY + topSpeed);
    }

    /// collision
    Vec2 plyPos = getPosition(); // top left corner
    // update sensor positions:
    float sensorOffset = 4.f;
    leftSensor.x = plyPos.x - sensorOffset;
    leftSensor.y = plyPos.y + (SCALE * sprite.getLocalBounds().height / 4.f);
    leftSensor.active = false;
    rightSensor.x = plyPos.x + (SCALE * sprite.getLocalBounds().width) + sensorOffset;
    rightSensor.y = plyPos.y + (SCALE * sprite.getLocalBounds().height / 4.f);
    rightSensor.active = false;
    bottomSensor.x = plyPos.x + (SCALE * sprite.getLocalBounds().width / 2.f);
    bottomSensor.y = plyPos.y + (SCALE * sprite.getLocalBounds().height) + sensorOffset;
    bottomSensor.active = false;

    Vec2 ePos;
    sf::FloatRect r;
    for (auto e: World::getInstance()->getEntities()) {
        if (e->getType() == Type::wall) {
            r.left = e->getPosition().x;
            r.top = e->getPosition().y;
            r.height = TILESIZE * SCALE;
            r.width = TILESIZE * SCALE;

            if (r.contains(bottomSensor.x, bottomSensor.y)) {
                bottomSensor.active = true;
            } else if (r.contains(leftSensor.x, leftSensor.y)) {
                leftSensor.active = true;
            } else if (r.contains(rightSensor.x, rightSensor.y)) {
                rightSensor.active = true;
            }
        }
    }
    if (bottomSensor.active) state = PlyState::standingOnTile;
    else if (leftSensor.active) state = PlyState::onLeftWall;
    else if (rightSensor.active) state = PlyState::onRightWall;
    else state = PlyState::onAir;

    for (auto e: World::getInstance()->getEntities()) {
        // player with wall
        if (e->getType() == Type::wall) {
            Vec2 overlapPly = World::getInstance()->getOverlap(plyPos, e->getPosition());
            bool thereIsCollision = overlapPly.x > 0.f && overlapPly.y > 0.f;

            if (thereIsCollision) {
                if (overlapPly.y < overlapPly.x) { // compensate only the shortest overlap, in this case y
                    if (bottomSensor.active) { // player on top of tile
                        plyPos.y -= overlapPly.y;
                    } else { // player hit tile from below
                        plyPos.y += overlapPly.y;
                    }
                } else { // compensate only x
                    if (rightSensor.active) { // player colliding on right wall
                        plyPos.x -= overlapPly.x;
                    } else if (leftSensor.active) { // player colliding on left wall
                        plyPos.x += overlapPly.x;
                    }
                }
                sprite.setPosition(plyPos.x, plyPos.y);
            }
        }
            // player with goal (bandage girl)
        else if (e->getType() == Type::goal) {
            Vec2 overlapPly = World::getInstance()->getOverlap(plyPos, e->getPosition());
            bool thereIsCollision = overlapPly.x > 0.f && overlapPly.y > 0.f;
            if (thereIsCollision) reachedGoal = true;
        }
    }
}

void Player::draw() {
    Game::getWindow()->draw(sprite);
}

Vec2 Player::getPosition() {
    return Vec2(sprite.getPosition().x, sprite.getPosition().y);
}

void Player::startLevel(int x, int y) {
    reachedGoal = false;
    sprite.setPosition(x, y);

}