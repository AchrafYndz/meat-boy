#include "Wall.h"
#include "../view/EntityView.h"
#include "../controller/Game.h"
#include "World.h"

#include <iostream>

Wall::Wall(Vec2 pos) : Entity(Type::wall) {
	texture.loadFromFile("resources/sprites/wall-sprite.png");
	sprite.setTexture(texture);
	sprite.setPosition(pos.x, pos.y);
	sprite.setScale(SCALE, SCALE);
}

void Wall::update()
{

}

void Wall::draw()
{
	observer->draw(sprite);
}


