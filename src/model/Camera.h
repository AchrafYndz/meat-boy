#ifndef INC_2022_PROJECT_ACHRAFYNDZ_CAMERA_H
#define INC_2022_PROJECT_ACHRAFYNDZ_CAMERA_H

#include "Entity.h"
#include "World.h"
#include <memory>

struct Vec2;

class Camera {
private:
    // 480 p
    const int windowWidth = 480;
    const int windowHeight = 853;

    // 720p
    //    const int windowWidth = 720;
    //    const int windowHeight = 1280;

    Camera() = default;

    static std::shared_ptr<Camera> theCamera;

    double cameraCenter;

public:
    Camera(Camera& other) = delete;

    void operator=(const Camera& other) = delete;

    // Getters
    int getWindowWidth() const { return windowWidth; }

    int getWindowHeight() const { return windowHeight; }

    int getCameraCenter() const { return cameraCenter; }

    void setCameraCenter(double h) { cameraCenter = h - (windowHeight / 2.f); }

    static std::shared_ptr<Camera> getInstance();

    void move(double diff);

    bool entityIsVisible(std::shared_ptr<Entity> e);

    void update(std::shared_ptr<Entity> entity);
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_CAMERA_H
