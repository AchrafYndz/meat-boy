#include "Goal.h"
#include "Camera.h"

Model::Goal::Goal(floatVector2 position_) : Entity(Type::goal) { position = position_; }

void Model::Goal::update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Camera> camera) {
    floatVector2 pixelPosition = camera->toPixels(position);
    notifyObservers(pixelPosition.x, pixelPosition.y, camera, false);
}
