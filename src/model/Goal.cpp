#include "Goal.h"
#include "../controller/Game.h"
#include "Camera.h"

Goal::Goal(Vec2 pos) : Entity(Type::goal) {
	position = pos;
}

void Goal::update()
{
	Vec2 pos = Camera::getInstance()->toPixels(position);
	notifyObservers(pos.x, pos.y);
}

void Goal::draw()
{
	Vec2 pos = Camera::getInstance()->toPixels(position);
	entView->draw(pos);
}

