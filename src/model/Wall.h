#ifndef INC_2022_PROJECT_ACHRAFYNDZ_WALL_H
#define INC_2022_PROJECT_ACHRAFYNDZ_WALL_H

#include "Entity.h"
#include "ObserverPattern.h"
#include "../util/Vec2.h"


namespace Model {

class Wall : public Entity, public Subject {
public:
    explicit Wall(Vec2 pos);
    ~Wall() override = default;

    void update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Camera> camera) override;
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_WALL_H