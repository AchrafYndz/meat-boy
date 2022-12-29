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

const double TIME_PER_FRAME = 1 / 60.0;
const float TILESIZE = 256;
// SCALE for 480p
const float SCALE = (WINDOW_WIDTH / 15) / TILESIZE;

namespace Model {
class Camera {
private:
    double cameraCenter;

    float totalHeight = 0; // total rows
public:
    Camera() = default;

    void setHeight(int rows) { totalHeight = rows; }

    Vec2 normalizedPosition(Vec2 pos);
    Vec2 toPixels(Vec2 pos) const;

    // Getters
    int getCameraCenter() const { return cameraCenter; }

    void setCameraCenter(double h);

    void move(double diff);

    bool entityIsVisible(int y);

    void update(std::shared_ptr<Player> player, std::shared_ptr<Controller::StateManager> stateManager);
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_CAMERA_H
