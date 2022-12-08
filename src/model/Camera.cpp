#include "Camera.h"
#include "Entity.h"
#include "World.h"
#include "../controller/StateManager.h"

std::unique_ptr<Camera> Camera::theCamera(new Camera);

Camera* Camera::getInstance() { return theCamera.get(); }

void Camera::move(double diff) {
    if (cameraCenter + diff - windowHeight / 2 >= 0)
        cameraCenter += diff;
}

bool Camera::entityIsVisible(Entity* e) {
    Vec2 ePos = e->getPosition();
    if (ePos.y < cameraCenter + (windowHeight / 2) && ePos.y + TILESIZE * SCALE > cameraCenter - (windowHeight / 2)) {
        return true;
    } else {
        return false;
    }
}

void Camera::update(Entity* entity) {
    // Move if autoscrolling
	if (StateManager::getInstance()->currentLevelHasAutoScroll()) {
		move(-0.02f);
	}
	// if player above 80% of the level, move also
	double playerHeight = entity->getPosition().y;
	double diff = playerHeight - (cameraCenter - (windowHeight * 0.3));
	if (diff < 0)
		move(diff);

}
