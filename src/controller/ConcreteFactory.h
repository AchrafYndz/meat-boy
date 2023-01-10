#ifndef INC_2022_PROJECT_ACHRAFYNDZ_CONCRETEFACTORY_H
#define INC_2022_PROJECT_ACHRAFYNDZ_CONCRETEFACTORY_H

#include "../model/AbstractFactory.h"
#include "../util/floatVector2.h"

#include <memory>

namespace Controller {
class ConcreteFactory : public Controller::AbstractFactory {
public:
    ConcreteFactory() = default;

    std::shared_ptr<Model::Entity> createEntity(const std::shared_ptr<Model::World>& world, Model::Entity::Type type,
                                                floatVector2 position) override;
};
} // namespace Controller

#endif // INC_2022_PROJECT_ACHRAFYNDZ_CONCRETEFACTORY_H
