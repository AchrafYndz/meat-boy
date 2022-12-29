#include "Wall.h"
#include "Camera.h"
#include "World.h"

#include <iostream>

Model::Wall::Wall(Vec2 pos) : Entity(Type::wall) { position = pos; }

void Model::Wall::update(std::shared_ptr<Camera> camera) {
    Vec2 pos = camera->toPixels(position);
    notifyObservers(pos.x, pos.y, camera);
}
