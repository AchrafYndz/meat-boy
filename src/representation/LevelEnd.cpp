#include "LevelEnd.h"
#include "Game.h"
#include "../logic/World.h"

LevelEnd::LevelEnd(int x, int y) : Entity(Type::end) {
    texture.loadFromFile("end-sprite.png");

    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(SCALE, SCALE);
}

void LevelEnd::update() {

}

void LevelEnd::draw() {
    Game::getWindow()->draw(sprite);
}

Vec2 LevelEnd::getPosition() {
    return {sprite.getPosition().x, sprite.getPosition().y};
}
