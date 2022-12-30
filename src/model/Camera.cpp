#include "Camera.h"
#include "Player.h"
#include "World.h"

Model::Vec2 Model::Camera::normalizedPosition(Vec2 pos) const {
    Vec2 result;

    float oldMin = 0;
    float oldMax = float(totalHeight) * SCALE * TILE_SIZE;
    float newMin = -1;
    float newMax = float(totalHeight);

    float oldPercent = (pos.y - oldMin) / (oldMax - oldMin);
    result.y = ((newMax - newMin) * oldPercent + newMin);

    result.x = ((2.f * pos.x) / WINDOW_WIDTH) - 1.f;

    return result;
}

Model::Vec2 Model::Camera::toPixels(Vec2 pos) const {
    Vec2 result;

    float oldMin = -1;
    float oldMax = float(totalHeight);
    float newMin = 0;
    float newMax = float(totalHeight) * SCALE * TILE_SIZE;

    float oldPercent = (pos.y - oldMin) / (oldMax - oldMin);
    result.y = ((newMax - newMin) * oldPercent + newMin);

    result.x = ((pos.x + 1.f) / 2.f) * WINDOW_WIDTH;

    return result;
}

void Model::Camera::move(float diff) {
    if (cameraCenter + diff - float(WINDOW_HEIGHT) / 2 >= 0)
        cameraCenter += diff;
}

bool Model::Camera::entityIsVisible(float y) const {
    // x will always be visible

    double upperLimit = cameraCenter - WINDOW_HEIGHT / 2.f;
    double lowerLimit = cameraCenter + WINDOW_HEIGHT / 2.f;

    return (y + SCALE * TILE_SIZE >= upperLimit && y <= lowerLimit);
}

void Model::Camera::setCameraCenter(float h) { cameraCenter = h - (WINDOW_HEIGHT / 2.f); }

void Model::Camera::update(const std::shared_ptr<Player>& player, const std::shared_ptr<Controller::StateManager>& stateManager) {
    // Move if auto scrolling
    if (stateManager->currentLevelHasAutoScroll()) {
        move(-0.5f);
    }
    // if player above 80% of the level, move also
    float playerHeight = toPixels(player->getPosition()).y;
    float diff = playerHeight - (cameraCenter - (WINDOW_HEIGHT * 0.3f));
    if (diff < 0.0f)
        move(diff);
}
