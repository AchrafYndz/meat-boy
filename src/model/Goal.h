#ifndef INC_2022_PROJECT_ACHRAFYNDZ_GOAL_H
#define INC_2022_PROJECT_ACHRAFYNDZ_GOAL_H

#include "Entity.h"
#include "ObserverPattern.h"

namespace Model {
/**
 * The Goal class represents the goal in the game.
 * It inherits from the Entity base class and also implements the Subject interface for the observer pattern.
 */
class Goal : public Entity, public Subject {
public:
    /**
     *  Constructor for the Goal class
     *
     *  @param position_ The position of the goal
     */
    explicit Goal(floatVector2 position_);

    /**
     *  Default Destructor for the Goal class
     */
    ~Goal() override = default;

    /**
     *  Update the goal
     *
     *  @param world The game world
     *  @param camera The camera
     */
    void update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Camera> camera) override;
};

} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_GOAL_H