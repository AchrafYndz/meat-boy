#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ABSTRACTFACTORY_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ABSTRACTFACTORY_H

#include "Entity.h"
#include <memory>

class Entity;

namespace Controller {
class AbstractFactory {
public:
    ~AbstractFactory() = default;

    virtual std::shared_ptr<Model::Entity> createEntity(const std::shared_ptr<Model::World>& world,
                                                        Model::Entity::Type type, floatVector2 position) = 0;
};
} // namespace Controller

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ABSTRACTFACTORY_H
