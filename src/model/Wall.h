#ifndef INC_2022_PROJECT_ACHRAFYNDZ_WALL_H
#define INC_2022_PROJECT_ACHRAFYNDZ_WALL_H

#include "../util/floatVector2.h"
#include "Entity.h"
#include "ObserverPattern.h"

namespace Model {

class Wall : public Entity, public Subject {
public:
    explicit Wall(floatVector2 position_);
    ~Wall() override = default;

    void update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Camera> camera) override;
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_WALL_H