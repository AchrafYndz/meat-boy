#include "Goal.h"
#include "Camera.h"

Goal::Goal(Vec2 pos) : Entity(Type::goal) { position = pos; }

void Goal::update(std::shared_ptr<Camera> camera) {
    Vec2 pos = camera->toPixels(position);
    notifyObservers(pos.x, pos.y, camera);
}
