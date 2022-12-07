#include "World.h"
#include "Entity.h"
#include "Camera.h"

std::unique_ptr<World> World::world(new World);

World::World() {

}

World *World::getInstance() {
    return world.get();
}

Vec2 World::getOverlap(Vec2 aPos, Vec2 bPos) {
    Vec2 result = Vec2(-1, -1);

    // X
    if (aPos.x < bPos.x) result.x = (TILESIZE * SCALE) - (bPos.x - aPos.x);
    else result.x = (TILESIZE * SCALE) - (aPos.x - bPos.x);
    // Y
    if (aPos.y < bPos.y) result.y = (TILESIZE * SCALE) - (bPos.y - aPos.y);
    else result.y = (TILESIZE * SCALE) - (aPos.y - bPos.y);

    // if there is no collision, it will return negative values
    return result;
}

void World::clearEntities() {
    for (auto &entity: entities) {
        if (entity->getType() != Entity::Type::player) delete entity;
    }
    entities.clear();
}

void World::drawAll() {
    Camera *camera = Camera::getInstance();
    for (auto &entity: entities) {
        if (entity->getType() == Entity::Type::player)
            camera->update(entity);
        if (camera->entityIsVisible(entity))
            entity->draw();
    }
}
