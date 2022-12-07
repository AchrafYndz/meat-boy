#include "Wall.h"

#include <iostream>
#include "World.h"
#include "../controller/Game.h"

Wall::Wall(Vec2 p) : Entity(Type::wall) {
    texture.loadFromFile("resources/sprites/wall-sprite.png");

    sprite.setTexture(texture);
    sprite.setPosition(p.x, p.y);
    sprite.setScale(SCALE, SCALE);
}

void Wall::draw() {
    Game::getWindow()->draw(sprite);
}

Vec2 Wall::getPosition() {
    return {sprite.getPosition().x, sprite.getPosition().y};
}