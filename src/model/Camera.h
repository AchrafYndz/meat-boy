#ifndef INC_2022_PROJECT_ACHRAFYNDZ_CAMERA_H
#define INC_2022_PROJECT_ACHRAFYNDZ_CAMERA_H

#include "../util/floatVector2.h"
#include "Entity.h"
#include "World.h"
#include <memory>

/// Constants
// 480 p
const int WINDOW_WIDTH = 480;
const int WINDOW_HEIGHT = 853;

// 720p
// const int WINDOW_WIDTH = 720;
// const int WINDOW_HEIGHT = 1280;

const float TIME_PER_FRAME = 1 / 60.0f;
const int TILE_SIZE = 256;
const float SCALE = (WINDOW_WIDTH / 15.0f) / TILE_SIZE;

namespace Model {
class Camera {
private:
    float cameraCenter = WINDOW_HEIGHT / 2.0f;

    int totalHeight = 0; // total rows
public:
    Camera() = default;

    void setHeight(int rows) { totalHeight = rows; }

    [[nodiscard]] floatVector2 normalizePosition(floatVector2 position) const;
    [[nodiscard]] floatVector2 toPixels(floatVector2 position) const;

    [[nodiscard]] float getCameraCenter() const { return cameraCenter; }

    void setCameraCenter(float height);

    void move(float difference);

    [[nodiscard]] bool entityIsVisible(float y) const;

    void update(const std::shared_ptr<Player>& player, const std::shared_ptr<Controller::StateManager>& stateManager);
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_CAMERA_H
