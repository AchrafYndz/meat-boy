#include "Goal.h"
#include "../controller/Game.h"
#include "World.h"
#include "Camera.h"

Goal::Goal(Vec2 pos) : Entity(Type::goal) {
	texture.loadFromFile("resources/sprites/goal-sprite.png");

	position = pos;

	sprite.setTexture(texture);
	//sprite.setPosition(pos.x, pos.y);
	sprite.setScale(SCALE, SCALE);
}

void Goal::draw()
{
	Vec2 pos = Camera::getInstance()->toPixels(position);
	sprite.setPosition(pos.x, pos.y);

	observer->draw(sprite);
}

