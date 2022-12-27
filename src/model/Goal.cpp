#include "Goal.h"
#include "Camera.h"

Goal::Goal(Vec2 pos) : Entity(Type::goal) {
	position = pos;
}

void Goal::update()
{
	Vec2 pos = Camera::getInstance()->toPixels(position);
	notifyObservers(pos.x, pos.y);
}


