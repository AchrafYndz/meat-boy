#ifndef INC_2022_PROJECT_ACHRAFYNDZ_OBSERVERPATTERN_H
#define INC_2022_PROJECT_ACHRAFYNDZ_OBSERVERPATTERN_H

#include <iostream>
#include <memory>
#include <vector>

#include "Camera.h"

namespace Model {
// The Observer class defines an interface for observing the Player's state
class Observer {
public:
    virtual ~Observer() = default;

    // This method is called when an entity's state changes
    virtual void update(float x, float y, std::shared_ptr<Camera> camera, bool facingLeft) = 0;
};

// The Subject class allows Observers to register and be notified of changes
class Subject {
public:
    // Register an Observer to be notified of changes
    void registerObserver(const std::shared_ptr<Observer>& observer) { observers.push_back(observer); }

    // Notify all registered Observers of a change
    void notifyObservers(float x, float y, const std::shared_ptr<Camera>& camera, bool facingLeft) {
        for (auto& observer : observers) {
            observer->update(x, y, camera, facingLeft);
        }
    }

private:
    std::vector<std::shared_ptr<Observer>> observers;
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_OBSERVERPATTERN_H
