#include "Goal.h"
#include "Camera.h"

Model::Goal::Goal(Vec2 pos) : Entity(Type::goal) { position = pos; }

void Model::Goal::update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Camera> camera) {
    Vec2 pos = camera->toPixels(position);
    notifyObservers(pos.x, pos.y, camera, false);
}
