#ifndef INC_2022_PROJECT_ACHRAFYNDZ_OBSERVERPATTERN_H
#define INC_2022_PROJECT_ACHRAFYNDZ_OBSERVERPATTERN_H

#include <iostream>
#include <memory>
#include <vector>

#include "Camera.h"

namespace Model {
/**
 * The Observer class defines an interface for observing the Player's state
 */
class Observer {
public:
    /**
     * Virtual Default Destructor for the Observer class
     */
    virtual ~Observer() = default;

    /**
     * This method is called when an entity's state changes
     *
     * @param x x-coordinate of the entity
     * @param y y-coordinate of the entity
     * @param camera the game camera
     * @param facingLeft whether the entity is facing left
     */
    virtual void update(float x, float y, std::shared_ptr<Camera> camera, bool facingLeft) = 0;
};

/**
 * The Subject class allows Observers to register and be notified of changes
 */
class Subject {
public:
    /**
     * Register an Observer to be notified of changes
     * @param observer the observer that will be registered
     */
    void registerObserver(const std::shared_ptr<Observer>& observer) { observers.push_back(observer); }

    /**
     * Notify all registered Observers of a change
     *
     * @param x x-coordinate of the entity
     * @param y y-coordinate of the entity
     * @param camera the game camera
     * @param facingLeft whether the entity is facing left
     */
    void notifyObservers(float x, float y, const std::shared_ptr<Camera>& camera, bool facingLeft) {
        for (auto& observer : observers) {
            observer->update(x, y, camera, facingLeft);
        }
    }

private:
    /** A vector of shared pointers to observers */
    std::vector<std::shared_ptr<Observer>> observers;
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_OBSERVERPATTERN_H
