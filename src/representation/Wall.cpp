#include "Wall.h"

#include <iostream>
#include "../logic/World.h"
#include "Game.h"

Wall::Wall(Vec2 p) : Entity(Type::wall)
{
	texture.loadFromFile("wall.png");

	sprite.setTexture(texture);
	sprite.setPosition(p.x, p.y);
	sprite.setScale(SCALE, SCALE);
}

void Wall::draw() {
	Game::getWindow()->draw(sprite);
}

Vec2 Wall::getPosition() {
	return { sprite.getPosition().x, sprite.getPosition().y };
}