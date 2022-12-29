#include "Goal.h"
#include "Camera.h"

Model::Goal::Goal(Vec2 pos) : Entity(Type::goal) { position = pos; }

void Model::Goal::update(std::shared_ptr<Camera> camera) {
    Vec2 pos = camera->toPixels(position);
    notifyObservers(pos.x, pos.y, camera);
}
