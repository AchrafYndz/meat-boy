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

/**
 * The base class for all entities in the game.
 * This class provides basic functionality and properties that all entities share.
 */
class Entity {
protected:
    /** The normalized position of the entity */
    floatVector2 position;

    /** A shared pointer to the view of the entity */
    std::shared_ptr<EntityView> entityView;

public:
    /** Enumeration of possible entity types */
    enum Type { player, wall, goal };

    /** The type of the current entity instance */
    Type type;

    /**
     *  Constructor for the Entity class
     *
     *  @param type_ The type of the entity
     */
    explicit Entity(Type type_) { type = type_; }

    /**
     *  Default virtual destructor for the Entity class
     */
    virtual ~Entity() = default;

    /**
     *  Assign a view to the entity
     *
     *  @param view The view to assign
     */
    void assignView(std::shared_ptr<EntityView>& view) { entityView = view; }

    /**
     *  Get the type of the entity
     *
     *  @return The type of the entity
     */
    [[nodiscard]] Type getType() const { return type; }

    /**
     *  Update the entity
     *
     *  @param world The game world
     *  @param camera The camera
     */
    virtual void update(const std::shared_ptr<Model::World>& world, std::shared_ptr<Camera> camera) = 0;

    /**
     *  Get the position of the entity
     *
     *  @return The normalized position of the entity
     */
    floatVector2 getPosition() { return position; }
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H