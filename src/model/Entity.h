#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H

#include "../util/floatVector2.h"
#include <memory>
#include <utility>

class EntityView;

// namespace Model
namespace Model {
class World;
class Camera;
class Entity {
protected:
    floatVector2 position; // normalized position

    std::shared_ptr<EntityView> entityView;

public:
    enum Type { player, wall, goal };
    Type type;

    explicit Entity(Type t) { type = t; }
    virtual ~Entity() = default;

    void assignView(std::shared_ptr<EntityView>& v) { entityView = v; }

    [[nodiscard]] Type getType() const { return type; }

    virtual void update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Camera> camera) = 0;

    floatVector2 getPosition() { return position; }
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H