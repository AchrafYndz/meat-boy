#ifndef INC_2022_PROJECT_ACHRAFYNDZ_CONCRETEFACTORY_H
#define INC_2022_PROJECT_ACHRAFYNDZ_CONCRETEFACTORY_H

#include "AbstractFactory.h"

#include "../model/Entity.h"

#include <memory>

namespace Controller {
struct Vec2;
class ConcreteFactory : public AbstractFactory {
public:
    ConcreteFactory(ConcreteFactory& other) = delete;
    void operator=(const ConcreteFactory& other) = delete;
    static std::shared_ptr<ConcreteFactory> getInstance();

    std::shared_ptr<Model::Entity> CreateObject(Model::Entity::Type type, Model::Vec2 pos) override;

private:
    ConcreteFactory() = default;
    static std::shared_ptr<ConcreteFactory> concreteFactory;
};
} // namespace Controller

#endif // INC_2022_PROJECT_ACHRAFYNDZ_CONCRETEFACTORY_H
