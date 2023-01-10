#ifndef INC_2022_PROJECT_ACHRAFYNDZ_WALL_H
#define INC_2022_PROJECT_ACHRAFYNDZ_WALL_H

#include "../util/floatVector2.h"
#include "Entity.h"
#include "ObserverPattern.h"

namespace Model {

/**
 * Wall Class for representing wall entities in the game
 * This class is derived from the Entity base class and Subject class
 */
class Wall : public Entity, public Subject {

public:
    /**
     * Constructor for creating a new wall object
     * @param position_ Initial position of the wall
     */
    explicit Wall(floatVector2 position_);

    /**
     * Default Destructor for Wall class
     */
    ~Wall() override = default;

    /**
     *  Update method which updates the wall's position
     *  @param world A shared pointer to the game world
     *  @param camera A shared pointer to the camera
     */
    void update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Camera> camera) override;
};

} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_WALL_H