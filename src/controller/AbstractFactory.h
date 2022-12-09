#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ABSTRACTFACTORY_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ABSTRACTFACTORY_H

#include <memory>
#include "../model/Entity.h"

class Entity;

class AbstractFactory
{
public:
	~AbstractFactory() {}

	virtual std::shared_ptr<Entity> CreateObject(Entity::Type type, Vec2 pos) = 0;

private:

};



#endif // INC_2022_PROJECT_ACHRAFYNDZ_ABSTRACTFACTORY_H