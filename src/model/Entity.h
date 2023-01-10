#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H

#include <memory>
#include <utility>
#include "../util/Vec2.h"


// namespace Model
class EntityView;

namespace Model {
class World;
class Camera;
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

    virtual void update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Camera> camera) = 0;

    Vec2 getPosition() { return position; }
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H