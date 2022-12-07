#include "Goal.h"
#include "../controller/Game.h"
#include "World.h"

Goal::Goal(int x, int y) : Entity(Type::goal) {
    texture.loadFromFile("resources/sprites/goal-sprite.png");

    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(SCALE, SCALE);
}

void Goal::update() {

}

void Goal::draw() {
    Game::getWindow()->draw(sprite);
}

Vec2 Goal::getPosition() {
    return {sprite.getPosition().x, sprite.getPosition().y};
}
