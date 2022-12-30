#ifndef INC_2022_PROJECT_ACHRAFYNDZ_CAMERA_H
#define INC_2022_PROJECT_ACHRAFYNDZ_CAMERA_H

#include "Entity.h"
#include "World.h"
#include <memory>

struct Vec2;

/// Constants
// 480 p
const int WINDOW_WIDTH = 480;
const int WINDOW_HEIGHT = 853;

// 720p
// const int WINDOW_WIDTH = 720;
// const int WINDOW_HEIGHT = 1280;

const float TIME_PER_FRAME = 1 / 60.0f;
const int TILE_SIZE = 256;
// SCALE for 480p
const float SCALE = (WINDOW_WIDTH / 15.0f) / TILE_SIZE;

namespace Model {
class Camera {
private:
    float cameraCenter = 0.0;

    int totalHeight = 0; // total rows
public:
    Camera() = default;

    void setHeight(int rows) { totalHeight = rows; }

    [[nodiscard]] Vec2 normalizedPosition(Vec2 pos) const;
    [[nodiscard]] Vec2 toPixels(Vec2 pos) const;

    // Getters
    [[nodiscard]] float getCameraCenter() const { return cameraCenter; }

    void setCameraCenter(float h);

    void move(float diff);

    [[nodiscard]] bool entityIsVisible(float y) const;

    void update(const std::shared_ptr<Player>& player, const std::shared_ptr<Controller::StateManager>& stateManager);
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_CAMERA_H
