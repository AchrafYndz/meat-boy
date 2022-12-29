#ifndef INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H
#define INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H

#include "Entity.h"
#include "ObserverPattern.h"

namespace Model {
class Goal : public Entity, public Subject {
public:
    Goal(Vec2 pos);
    ~Goal() {}

    void update(std::shared_ptr<Camera> camera) override;
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H