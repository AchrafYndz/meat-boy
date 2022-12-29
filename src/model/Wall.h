#ifndef INC_2022_PROJECT_ACHRAFYNDZ_WALL_H
#define INC_2022_PROJECT_ACHRAFYNDZ_WALL_H

#include "Entity.h"
#include "ObserverPattern.h"

namespace Model {
struct Vec2;

class Wall : public Entity, public Subject {
public:
    Wall(Vec2 pos);
    ~Wall() {}

    void update(std::shared_ptr<Camera> camera) override;
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_WALL_H