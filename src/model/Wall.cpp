#include "Wall.h"
#include "../controller/Game.h"
#include "../view/EntityView.h"
#include "Camera.h"
#include "World.h"

#include <iostream>

Wall::Wall(Vec2 pos) : Entity(Type::wall) {
    texture.loadFromFile("resources/sprites/wall-sprite.png");

    position = pos;

    sprite.setTexture(texture);
    // sprite.setPosition(pos.x, pos.y);
    sprite.setScale(SCALE, SCALE);
}

void Wall::draw() {
    Vec2 pos = Camera::getInstance()->toPixels(position);
    sprite.setPosition(pos.x, pos.y);

    observer->draw(sprite);
}
