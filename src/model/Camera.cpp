#include "Camera.h"
#include "Entity.h"
#include "World.h"
#include "../controller/StateManager.h"

std::shared_ptr<Camera> Camera::theCamera(new Camera);

std::shared_ptr<Camera> Camera::getInstance() { return theCamera; }

void Camera::move(double diff) {
    if (cameraCenter + diff - windowHeight / 2 >= 0)
        cameraCenter += diff;
}

bool Camera::entityIsVisible(std::shared_ptr<Entity> e) {
    Vec2 ePos = e->getPosition();
    if (ePos.y < cameraCenter + (windowHeight / 2) && ePos.y + TILESIZE * SCALE > cameraCenter - (windowHeight / 2)) {
        return true;
    } else {
        return false;
    }
}

void Camera::update(std::shared_ptr<Entity> entity) {
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
