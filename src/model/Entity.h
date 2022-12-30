#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H

#include <memory>
#include <utility>

#include "World.h"

class EntityView;

namespace Model {
class Entity {
protected:
    Vec2 position; // normalized position

    std::shared_ptr<EntityView> entView;

public:
    enum Type { none, player, wall, goal };
    Type type = none;

    explicit Entity(Type t) { type = t; }
    virtual ~Entity() = default;

    void assignView(std::shared_ptr<EntityView>& v) { entView = v; }

    [[nodiscard]] Type getType() const { return type; }

    virtual void update(std::shared_ptr<Camera> camera) = 0;

    Vec2 getPosition() { return position; }
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H