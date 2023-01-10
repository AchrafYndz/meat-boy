#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ABSTRACTFACTORY_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ABSTRACTFACTORY_H

#include "Entity.h"
#include <memory>

namespace Controller {

/**
 *  AbstractFactory is an interface class that defines the methods that should be implemented
 *  by the ConcreteFactory to create different types of entities
 */
class AbstractFactory {
public:
    /**
     * Default Destructor for the AbstractFactory class
     */
    virtual ~AbstractFactory() = default;

    /**
     *  This pure virtual method defines the outline of how an entity should be created based on
     *  the specified type of entity, the position of the entity and the world it should be added to
     *
     *  @param world A shared pointer to the world the entity should be added to
     *  @param type The type of entity to be created
     *  @param position The position of the entity
     *
     *  @return A shared pointer to the created entity
     */
    virtual std::shared_ptr<Model::Entity> createEntity(const std::shared_ptr<Model::World>& world,
                                                        Model::Entity::Type type, floatVector2 position) = 0;
};
} // namespace Controller

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ABSTRACTFACTORY_H
