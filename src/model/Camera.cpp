#include "Camera.h"
#include "Player.h"
#include "World.h"

floatVector2 Model::Camera::normalizePosition(floatVector2 position) const {
    floatVector2 result;

    float oldMin = 0.0f;
    float oldMax = static_cast<float>(totalHeight) * SCALE * TILE_SIZE;
    float newMin = -1.0f;
    float newMax = static_cast<float>(totalHeight);

    float oldPercent = (position.y - oldMin) / (oldMax - oldMin);

    result.y = ((newMax - newMin) * oldPercent + newMin);
    result.x = ((2.0f * position.x) / WINDOW_WIDTH) - 1.0f;

    return result;
}

floatVector2 Model::Camera::toPixels(floatVector2 position) const {
    floatVector2 result;

    float oldMin = -1.0f;
    float oldMax = static_cast<float>(totalHeight);
    float newMin = 0.0f;
    float newMax = static_cast<float>(totalHeight) * SCALE * TILE_SIZE;

    float oldPercent = (position.y - oldMin) / (oldMax - oldMin);

    result.y = ((newMax - newMin) * oldPercent + newMin);
    result.x = ((position.x + 1.0f) / 2.0f) * WINDOW_WIDTH;

    return result;
}

void Model::Camera::move(float difference) {
    if (cameraHeight + difference - static_cast<float>(WINDOW_HEIGHT) / 2.0f >= 0)
        cameraHeight += difference;
}

bool Model::Camera::entityIsVisible(float y) const {
    double upperLimit = cameraHeight - WINDOW_HEIGHT / 2.0f;
    double lowerLimit = cameraHeight + WINDOW_HEIGHT / 2.0f;

    return (y + SCALE * TILE_SIZE >= upperLimit && y <= lowerLimit);
}

void Model::Camera::setCameraHeight(float height) { cameraHeight = height - (WINDOW_HEIGHT / 2.0f); }

void Model::Camera::update(const std::shared_ptr<Player>& player, const std::shared_ptr<Controller::StateManager>& stateManager) {
    // Move if auto scrolling
    if (stateManager->currentLevelHasAutoScroll()) {
        move(-0.5f);
    }
    // if player above 80% of the level, move also
    float playerHeight = toPixels(player->getPosition()).y;
    float difference = playerHeight - (cameraHeight - (WINDOW_HEIGHT * 0.3f));
    if (difference < 0.0f)
        move(difference);
}
