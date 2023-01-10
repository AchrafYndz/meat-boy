#ifndef INC_2022_PROJECT_ACHRAFYNDZ_CAMERA_H
#define INC_2022_PROJECT_ACHRAFYNDZ_CAMERA_H

#include "../util/floatVector2.h"
#include "Constants.h"
#include "Entity.h"
#include "World.h"
#include <memory>

namespace Model {
/**
 *  Camera class is responsible for handling the camera position and movement in the game world
 */
class Camera {
private:
    /** The y-coordinate of the camera */
    float cameraHeight = WINDOW_HEIGHT / 2.0f;

    /** The total number of rows in the world */
    int totalHeight = 0;
public:
    /**
     *  Default constructor for the Camera class
     */
    Camera() = default;

    /**
     *  Sets the total number of rows in the world as the total height
     *
     *  @param rows total number of rows
     */
    void setTotalHeight(int rows) { totalHeight = rows; }

    /**
     *  Normalizes the position of an entity based on the camera position
     *
     *  @param position The position of the entity
     *
     *  @return The normalized position of the entity
     */
    [[nodiscard]] floatVector2 normalizePosition(floatVector2 position) const;

    /**
     *  Converts the normalized position of an entity to pixels
     *
     *  @param position The normalized position of the entity
     *
     *  @return The position of the entity in pixels
     */
    [[nodiscard]] floatVector2 toPixels(floatVector2 position) const;

    /**
     *  Returns the y-coordinate of the center of the camera
     *
     *  @return The y-coordinate of the center of the camera
     */
    [[nodiscard]] float getCameraHeight() const { return cameraHeight; }

    /**
     *  Sets the camera height of the camera
     *
     *  @param height the height of the camera
     */
    void setCameraHeight(float height);

    /**
     *  Moves the camera up
     *
     *  @param difference the number of pixels the camera should move
     */
    void move(float difference);

    /**
     *  Returns whether an entity is visible or not
     *
     *  @param y The y-coordinate of the entity to check for visibility
     *
     *  @return True if entity is visible, false otherwise
     */
    [[nodiscard]] bool entityIsVisible(float y) const;

    /**
     *  Updates the camera position if the conditions are met
     *
     *  @param player A shared pointer to the player
     *  @param stateManager A shared pointer to the state manager
     */
    void update(const std::shared_ptr<Player>& player, const std::shared_ptr<Controller::StateManager>& stateManager);
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_CAMERA_H
