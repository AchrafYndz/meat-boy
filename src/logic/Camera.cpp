#include "Camera.h"
#include "Entity.h"
#include "World.h"


#include <iostream>

std::unique_ptr<Camera> Camera::theCamera(new Camera);

Camera *Camera::getInstance() {
    return theCamera.get();
}

void Camera::move(double diff) {
	cameraCenter += diff;
}

bool Camera::entityIsVisible(Entity *e) {
    Vec2 ePos = e->getPosition();
    if (ePos.y < cameraCenter + (windowHeight / 2) && ePos.y > cameraCenter - (windowHeight / 2)) {
        return true;
    } else {
        return false;
    }
}

void Camera::update(Entity *entity) {
    double playerHeight = entity->getPosition().y;
    double diff = playerHeight - (cameraCenter - (windowHeight * 0.3));
    if (diff < 0) {
        move(diff);
    }

}
