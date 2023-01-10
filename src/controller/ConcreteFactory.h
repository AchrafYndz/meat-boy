#ifndef INC_2022_PROJECT_ACHRAFYNDZ_CONCRETEFACTORY_H
#define INC_2022_PROJECT_ACHRAFYNDZ_CONCRETEFACTORY_H

#include "../model/AbstractFactory.h"
#include "../util/floatVector2.h"

#include <memory>

namespace Controller {

/**
 *  ConcreteFactory is a concrete implementation of the AbstractFactory interface
 *  that creates different types of entities based on the specified type and position
 */
class ConcreteFactory : public Controller::AbstractFactory {
public:
    /**
     *  Default constructor for the ConcreteFactory class
     */
    ConcreteFactory() = default;

    /**
     *  Creates an Entity based on the specified type, position and the world
     *
     *  @param world A shared pointer to the world the entity should be added to
     *  @param type The type of entity to be created
     *  @param position The position of the entity
     *
     *  @return A shared pointer to the created entity
     */
    std::shared_ptr<Model::Entity> createEntity(const std::shared_ptr<Model::World>& world, Model::Entity::Type type,
                                                floatVector2 position) override;
};
} // namespace Controller

#endif // INC_2022_PROJECT_ACHRAFYNDZ_CONCRETEFACTORY_H
