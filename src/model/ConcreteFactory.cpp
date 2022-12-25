#include "ConcreteFactory.h"

#include "Wall.h"
#include "Goal.h"
#include "Player.h"
#include "World.h"

std::shared_ptr<ConcreteFactory> ConcreteFactory::concreteFactory(new ConcreteFactory);

std::shared_ptr<ConcreteFactory> ConcreteFactory::getInstance() { return concreteFactory; }

std::shared_ptr<Entity> ConcreteFactory::CreateObject(Entity::Type type, Vec2 pos)
{
	switch (type)
	{
	case Entity::wall: {
		std::shared_ptr<EntityView> entView(new EntityView("resources/sprites/wall-sprite.png"));
		std::shared_ptr<Wall> wall(new Wall(pos));
		wall->registerObserver(entView);
		wall->assignView(entView);
		return wall;
	}
	case Entity::goal: {
		std::shared_ptr<EntityView> entView(new EntityView("resources/sprites/goal-sprite.png"));
		std::shared_ptr<Goal> goal(new Goal(pos));
		goal->registerObserver(entView);
		goal->assignView(entView);
		return goal;
    }
    case Entity::player: {
        std::shared_ptr<EntityView> entView(new EntityView("resources/sprites/player-sprite.png"));
        std::shared_ptr<Player> player(new Player(pos));
		player->registerObserver(entView);
        World::getInstance()->setPlayer(player);
		player->assignView(entView);
        return player;
    }
	default:
		break;
	}
	return nullptr;
}
