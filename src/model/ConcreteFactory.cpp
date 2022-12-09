#include "ConcreteFactory.h"

#include "Wall.h"
#include "Goal.h"
#include "World.h"

#include <SFML/Graphics.hpp>

std::shared_ptr<ConcreteFactory> ConcreteFactory::concreteFactory(new ConcreteFactory);

std::shared_ptr<ConcreteFactory> ConcreteFactory::getInstance() { return concreteFactory; }

std::shared_ptr<Entity> ConcreteFactory::CreateObject(Entity::Type type, Vec2 pos)
{
	switch (type)
	{
	case Entity::wall: {
		std::shared_ptr<EntityView> entView(new EntityView());
		std::shared_ptr<Wall> wall(new Wall(pos));
		wall->attachObserver(entView);
		return wall;
	}
		break;
	case Entity::goal: {
		std::shared_ptr<EntityView> entView(new EntityView());
		std::shared_ptr<Goal> goal(new Goal(pos));
		goal->attachObserver(entView);
		return goal;
	}
		break;
	default:
		break;
	}
	return nullptr;
}