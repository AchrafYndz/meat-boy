#include "Player.h"
#include "Game.h"

#include <iostream>

std::unique_ptr<Player> Player::player(new Player);

Player* Player::getInstance() {
	return player.get();
}

Player::Player() : Entity(Type::player) {
	texture.loadFromFile("player-sprite.png");

	sprite.setTexture(texture);
	sprite.setScale(SCALE, SCALE);
}

void Player::processInput() {
	int currentX = sprite.getPosition().x;

	// only accept input on the second half of the jump
	// or when the jump is normal (up)
	// or when not jumping
	if (currentJumpingTime < JUMPING_TOTAL_TIME / 2.f || jumpType == JumpType::normal || currentJumpingTime <= 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			currentAcceleration -= acceleration;
			sprite.setScale(-SCALE, SCALE);
			sprite.setOrigin(sprite.getLocalBounds().width, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			currentAcceleration += acceleration;
			sprite.setScale(SCALE, SCALE);
			sprite.setOrigin(0.f, 0.f);
		}
		else { // deceleration
			if (currentAcceleration > 0) currentAcceleration--;
			else if (currentAcceleration < 0) currentAcceleration++;
		}
	}
	if (currentAcceleration > topSpeed) currentAcceleration = topSpeed;
	else if (currentAcceleration < -topSpeed) currentAcceleration = -topSpeed;
	sprite.setPosition(currentX + currentAcceleration, sprite.getPosition().y);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && currentJumpingTime <= 0 && state != PlyState::onAir) {
		if (state == PlyState::standingOnTile) jumpType = JumpType::normal;
		else if (state == PlyState::onLeftWall) jumpType = JumpType::toTheRight;
		else if (state == PlyState::onRightWall) jumpType = JumpType::toTheLeft;
		currentAcceleration = 0; // stop acceleration
		currentJumpingTime = JUMPING_TOTAL_TIME;
	}
}

void Player::update()
{
	processInput();

	int currentY = sprite.getPosition().y;
	if (currentJumpingTime > 0) {
		if (jumpType == JumpType::normal)
			sprite.setPosition(sprite.getPosition().x, currentY - topSpeed);
		else if (jumpType == JumpType::toTheLeft)
			sprite.setPosition(sprite.getPosition().x - topSpeed, currentY - topSpeed);
		else if (jumpType == JumpType::toTheRight)
			sprite.setPosition(sprite.getPosition().x + topSpeed, currentY - topSpeed);

		currentJumpingTime -= TIME_PER_FRAME;
	}
	else { // apply gravity
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
	for (auto e : World::getInstance()->getEntities()) {
		if (e->getType() == Type::wall) {
			r.left = e->getPosition().x;
			r.top = e->getPosition().y;
			r.height = TILESIZE * SCALE;
			r.width = TILESIZE * SCALE;

			if (r.contains(bottomSensor.x, bottomSensor.y)) {
				bottomSensor.active = true;
			}
			else if (r.contains(leftSensor.x, leftSensor.y)) {
				leftSensor.active = true;
			}
			else if (r.contains(rightSensor.x, rightSensor.y)) {
				rightSensor.active = true;
			}
		}
	}
	if (bottomSensor.active) state = PlyState::standingOnTile;
	else if (leftSensor.active) state = PlyState::onLeftWall;
	else if (rightSensor.active) state = PlyState::onRightWall;
	else state = PlyState::onAir;

	for (auto e : World::getInstance()->getEntities())
	{
		if (e->getType() == Type::wall) {
			ePos.x = e->getPosition().x;
			ePos.y = e->getPosition().y;
			Vec2 overlapPly = World::getInstance()->getOverlap(plyPos, e->getPosition());
			bool thereIsCollision = overlapPly.x > 0.f && overlapPly.y > 0.f;

			if (thereIsCollision) {
				if (overlapPly.y < overlapPly.x) { // compensate only the shortest overlap, in this case y
					if (bottomSensor.active) { // player on top of tile
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
				sprite.setPosition(plyPos.x, plyPos.y);
			}
		}
	}
}

void Player::draw()
{
	Game::getWindow()->draw(sprite);

	// Debug Sensors:
	/*sf::Vertex lineLeft1[] =
	{
		sf::Vertex(sf::Vector2f(leftSensor.x - 2.f, leftSensor.y - 2.f)),
		sf::Vertex(sf::Vector2f(leftSensor.x + 2.f, leftSensor.y + 2.f))
	};
	sf::Vertex lineLeft2[] =
	{
		sf::Vertex(sf::Vector2f(leftSensor.x - 2.f, leftSensor.y + 2.f)),
		sf::Vertex(sf::Vector2f(leftSensor.x + 2.f, leftSensor.y - 2.f))
	};
	Game::getWindow()->draw(lineLeft1, 2, sf::Lines);
	Game::getWindow()->draw(lineLeft2, 2, sf::Lines);
	sf::Vertex lineRight1[] =
	{
		sf::Vertex(sf::Vector2f(rightSensor.x - 2.f, rightSensor.y - 2.f)),
		sf::Vertex(sf::Vector2f(rightSensor.x + 2.f, rightSensor.y + 2.f))
	};
	sf::Vertex lineRight2[] =
	{
		sf::Vertex(sf::Vector2f(rightSensor.x - 2.f, rightSensor.y + 2.f)),
		sf::Vertex(sf::Vector2f(rightSensor.x + 2.f, rightSensor.y - 2.f))
	};
	Game::getWindow()->draw(lineRight1, 2, sf::Lines);
	Game::getWindow()->draw(lineRight2, 2, sf::Lines);
	sf::Vertex lineBottom1[] =
	{
		sf::Vertex(sf::Vector2f(bottomSensor.x - 2.f, bottomSensor.y - 2.f)),
		sf::Vertex(sf::Vector2f(bottomSensor.x + 2.f, bottomSensor.y + 2.f))
	};
	sf::Vertex lineBottom2[] =
	{
		sf::Vertex(sf::Vector2f(bottomSensor.x - 2.f, bottomSensor.y + 2.f)),
		sf::Vertex(sf::Vector2f(bottomSensor.x + 2.f, bottomSensor.y - 2.f))
	};
	Game::getWindow()->draw(lineBottom1, 2, sf::Lines);
	Game::getWindow()->draw(lineBottom2, 2, sf::Lines);*/
}

Vec2 Player::getPosition() {
	return Vec2(sprite.getPosition().x, sprite.getPosition().y);
}

void Player::setInitialPosition(int x, int y)
{
	sprite.setPosition(x, y);
}
