#include "ConcreteFactory.h"

#include "../model/Goal.h"
#include "../model/Player.h"
#include "../model/Wall.h"

#include "../view/EntityView.h"

std::shared_ptr<Controller::ConcreteFactory> Controller::ConcreteFactory::concreteFactory(new ConcreteFactory);

std::shared_ptr<Controller::ConcreteFactory> Controller::ConcreteFactory::getInstance() { return concreteFactory; }

std::shared_ptr<Model::Entity> Controller::ConcreteFactory::CreateEntity(Model::Entity::Type type, Model::Vec2 pos) {
    switch (type) {
    case Model::Entity::wall: {
        std::shared_ptr<EntityView> entView(new EntityView("resources/sprites/wall-sprite.png"));
        std::shared_ptr<Model::Wall> wall(new Model::Wall(pos));
        wall->registerObserver(entView);
        wall->assignView(entView);
        return wall;
    }
    case Model::Entity::goal: {
        std::shared_ptr<EntityView> entView(new EntityView("resources/sprites/goal-sprite.png"));
        std::shared_ptr<Model::Goal> goal(new Model::Goal(pos));
        goal->registerObserver(entView);
        goal->assignView(entView);
        return goal;
    }
    case Model::Entity::player: {
        std::shared_ptr<EntityView> entView(new EntityView("resources/sprites/player-sprite.png"));
        std::shared_ptr<Model::Player> player(new Model::Player(pos));
        player->registerObserver(entView);
        Model::World::getInstance()->setPlayer(player);
        player->assignView(entView);
        return player;
    }
    default:
        break;
    }
    return nullptr;
}
