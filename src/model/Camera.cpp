#include "Camera.h"
#include "Entity.h"
#include "Player.h"
#include "World.h"
#include "../controller/StateManager.h"

std::shared_ptr<Camera> Camera::theCamera(new Camera);

Vec2 Camera::normalizedPosition(Vec2 pos)
{
    Vec2 result;

	/*
	old: 0 to totalHeight * SCALE * TILESIZE
	new: -1 to totalHeight
	*/

	float oldMin =  0;
	float oldMax = totalHeight * SCALE * TILESIZE;
	float newMin = -1;
	float newMax = totalHeight;

	float oldPercent = (pos.y - oldMin) / (oldMax - oldMin);
	result.y = ((newMax - newMin) * oldPercent + newMin);

	result.x = ((2.f * pos.x) / windowWidth) - 1.f;
   // result.y = (((totalHeight+1) * pos.y) / windowHeight) - 1.f;

	return result;
}

Vec2 Camera::toPixels(Vec2 pos) const
{
    Vec2 result;

	float oldMin = -1;
	float oldMax = totalHeight;
	float newMin = 0;
	float newMax = totalHeight * SCALE * TILESIZE;

	float oldPercent = (pos.y - oldMin) / (oldMax - oldMin);
	result.y = ((newMax - newMin) * oldPercent + newMin);

	result.x = ((pos.x + 1.f) / 2.f) * windowWidth;
    //result.y = ((pos.y + 1.f) / (totalHeight + 1.f)) * windowHeight;

	return result;
}

std::shared_ptr<Camera> Camera::getInstance() { return theCamera; }

void Camera::move(double diff) {
    if (cameraCenter + diff - windowHeight / 2 >= 0)
        cameraCenter += diff;
}

bool Camera::entityIsVisible(std::shared_ptr<Entity> e) {
    Vec2 ePos = toPixels(e->getPosition());

	// x will always be visible

	float upperLimit = cameraCenter - windowHeight / 2.f;
	float lowerLimit = cameraCenter + windowHeight / 2.f;

	return (ePos.y + SCALE * TILESIZE >= upperLimit && ePos.y <= lowerLimit);
}

void Camera::setCameraCenter(double h)
{
	cameraCenter = h - (windowHeight / 2.f);
}

void Camera::update(std::shared_ptr<Player> player) {
    // Move if autoscrolling
	if (StateManager::getInstance()->currentLevelHasAutoScroll()) {
		move(-0.02f);
	}
	// if player above 80% of the level, move also
	double playerHeight = toPixels(player->getPosition()).y;
	double diff = playerHeight - (cameraCenter - (windowHeight * 0.3));
	if (diff < 0)
		move(diff);
}
