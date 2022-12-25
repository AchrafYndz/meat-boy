#include "Wall.h"
#include "../controller/Game.h"
#include "../view/EntityView.h"
#include "Camera.h"
#include "World.h"

#include <iostream>

Wall::Wall(Vec2 pos) : Entity(Type::wall) {
    position = pos;
}

void Wall::update()
{
	Vec2 pos = Camera::getInstance()->toPixels(position);
	notifyObservers(pos.x, pos.y);
}

void Wall::draw() {
	Vec2 pos = Camera::getInstance()->toPixels(position);
	entView->draw(pos);
}
