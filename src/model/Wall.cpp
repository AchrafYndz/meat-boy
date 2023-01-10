#include "Wall.h"
#include "Camera.h"
#include "World.h"

Model::Wall::Wall(floatVector2 position_) : Entity(Type::wall) { position = position_; }

void Model::Wall::update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Camera> camera) {
    floatVector2 pixelPosition = camera->toPixels(position);
    notifyObservers(pixelPosition.x, pixelPosition.y, camera, false);
}
