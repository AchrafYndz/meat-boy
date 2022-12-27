#ifndef INC_2022_PROJECT_ACHRAFYNDZ_CONCRETEFACTORY_H
#define INC_2022_PROJECT_ACHRAFYNDZ_CONCRETEFACTORY_H

#include "AbstractFactory.h"

#include "../model/Entity.h"

#include <memory>

struct Vec2;

class ConcreteFactory : public AbstractFactory
{
public:
	ConcreteFactory(ConcreteFactory& other) = delete;
	void operator=(const ConcreteFactory& other) = delete;
	static std::shared_ptr<ConcreteFactory> getInstance();

	std::shared_ptr<Entity> CreateObject(Entity::Type type, Vec2 pos);

private:
	ConcreteFactory() {}
	static std::shared_ptr<ConcreteFactory> concreteFactory;
};



#endif // INC_2022_PROJECT_ACHRAFYNDZ_CONCRETEFACTORY_H
