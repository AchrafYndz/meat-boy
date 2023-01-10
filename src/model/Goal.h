#ifndef INC_2022_PROJECT_ACHRAFYNDZ_GOAL_H
#define INC_2022_PROJECT_ACHRAFYNDZ_GOAL_H

#include "Entity.h"
#include "ObserverPattern.h"

namespace Model {
class Goal : public Entity, public Subject {
public:
    explicit Goal(floatVector2 position_);
    ~Goal() override = default;

    void update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Camera> camera) override;
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_GOAL_H