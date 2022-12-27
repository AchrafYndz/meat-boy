#include "Camera.h"
#include "Entity.h"
#include "Player.h"
#include "World.h"

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

	result.x = ((2.f * pos.x) / WINDOW_WIDTH) - 1.f;
   // result.y = (((totalHeight+1) * pos.y) / WINDOW_HEIGHT) - 1.f;

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

	result.x = ((pos.x + 1.f) / 2.f) * WINDOW_WIDTH;
    //result.y = ((pos.y + 1.f) / (totalHeight + 1.f)) * WINDOW_HEIGHT;

	return result;
}

void Camera::move(double diff) {
    if (cameraCenter + diff - WINDOW_HEIGHT / 2 >= 0)
        cameraCenter += diff;
}

bool Camera::entityIsVisible(int y) {
	// x will always be visible

	float upperLimit = cameraCenter - WINDOW_HEIGHT / 2.f;
	float lowerLimit = cameraCenter + WINDOW_HEIGHT / 2.f;

	return (y + SCALE * TILESIZE >= upperLimit && y <= lowerLimit);
}

void Camera::setCameraCenter(double h)
{
	cameraCenter = h - (WINDOW_HEIGHT / 2.f);
}

void Camera::update(std::shared_ptr<Player> player, std::shared_ptr<StateManager> stateManager) {
    // Move if autoscrolling
	if (stateManager->currentLevelHasAutoScroll()) {
		move(-0.5f);
	}
	// if player above 80% of the level, move also
	double playerHeight = toPixels(player->getPosition()).y;
	double diff = playerHeight - (cameraCenter - (WINDOW_HEIGHT * 0.3));
	if (diff < 0)
		move(diff);
}
