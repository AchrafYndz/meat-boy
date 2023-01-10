#include "ConcreteFactory.h"
#include "../model/Goal.h"
#include "../model/Player.h"
#include "../model/Wall.h"
#include "../view/EntityView.h"

std::shared_ptr<Model::Entity> Controller::ConcreteFactory::createEntity(const std::shared_ptr<Model::World>& world, Model::Entity::Type type,
                                                                         floatVector2 position) {
    switch (type) {
    case Model::Entity::wall: {
        std::shared_ptr<EntityView> entityView(new EntityView("resources/sprites/wall-sprite.png"));
        std::shared_ptr<Model::Wall> wall(new Model::Wall(position));
        wall->registerObserver(entityView);
        wall->assignView(entityView);
        return wall;
    }
    case Model::Entity::goal: {
        std::shared_ptr<EntityView> entityView(new EntityView("resources/sprites/goal-sprite.png"));
        std::shared_ptr<Model::Goal> goal(new Model::Goal(position));
        goal->registerObserver(entityView);
        goal->assignView(entityView);
        return goal;
    }
    case Model::Entity::player: {
        std::shared_ptr<EntityView> entityView(new EntityView("resources/sprites/player-sprite.png"));
        std::shared_ptr<Model::Player> player(new Model::Player(position));
        player->registerObserver(entityView);
        world->setPlayer(player);
        player->assignView(entityView);
        return player;
    }
    default:
        break;
    }
    return nullptr;
}
