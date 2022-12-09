#include "Goal.h"
#include "../controller/Game.h"
#include "World.h"

Goal::Goal(Vec2 pos) : Entity(Type::goal) {
	texture.loadFromFile("resources/sprites/goal-sprite.png");
	sprite.setTexture(texture);
	sprite.setPosition(pos.x, pos.y);
	sprite.setScale(SCALE, SCALE);
}

void Goal::update()
{

}

void Goal::draw()
{
	observer->draw(sprite);
}

