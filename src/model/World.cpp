#include "World.h"
#include "../controller/StateManager.h"
#include "../util/json.hpp"
#include "Camera.h"
#include "ConcreteFactory.h"
#include "Entity.h"
#include "Player.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::shared_ptr<World> World::world(new World);

World::World() {}

std::shared_ptr<World> World::getInstance() { return world; }

void World::loadLevel(int lvl, std::shared_ptr<StateManager> stateManager) {
    clearEntities();

    int tileSize = TILESIZE * SCALE;

    std::ifstream levelMap;
    std::ifstream levelsInfo("resources/levels/levels-info.json");

    nlohmann::json j;
    levelsInfo >> j;

    std::string lvlPath = j["level-" + std::to_string(lvl)]["filePath"];
    bool autoScrolling = j["level-" + std::to_string(lvl)]["autoScrolling"];

    stateManager->goToLevel(lvl, autoScrolling);

    levelMap.open(lvlPath);

    std::string line;
    char delimiter = ',';

    // get amount of rows
    int totalRows = 0;
    while (getline(levelMap, line))
        totalRows++;
    levelMap.clear();
    levelMap.seekg(0);                                            // return to the beginning
    Camera::getInstance()->setHeight(totalRows);                  // set total height of level
    Camera::getInstance()->setCameraCenter(totalRows * tileSize); // set initial camera position

    auto world_ = World::getInstance();
    std::string value;
    int column = 0;                             // top
    int row = 0;                                // left
    while (getline(levelMap, line)) {           /* read entire line into line */
        std::stringstream ss(line);             /* create stringstream from line */
        while (getline(ss, value, delimiter)) { /* read each field from line */
            Vec2 pos = Camera::getInstance()->normalizedPosition(Vec2(column * tileSize, row * tileSize));
            if (value == "0")
                world_->addEntity(ConcreteFactory::getInstance()->CreateObject(Entity::wall, pos));
            else if (value == "1") // goal
                world_->addEntity(ConcreteFactory::getInstance()->CreateObject(Entity::goal, pos));
            else if (value == "2") // player position
                world_->addEntity(ConcreteFactory::getInstance()->CreateObject(Entity::player, pos));

            column++;
        }
        row++;
        column = 0;
    }

    // Vec2 p= (Player::getInstance()->getPosition());
    // std::cout << p.x << ", " << p.y << std::endl;
    // p = Camera::getInstance()->toPixels(p);
    // std::cout << p.x << ", " << p.y << std::endl;
}

// Vec2 World::getOverlap(Vec2 aPos, Vec2 bPos) {
//     Vec2 result = Vec2(-1, -1);
//
//     // X
//     if (aPos.x < bPos.x)
//         result.x = (TILESIZE * SCALE) - (bPos.x - aPos.x);
//     else
//         result.x = (TILESIZE * SCALE) - (aPos.x - bPos.x);
//     // Y
//     if (aPos.y < bPos.y)
//         result.y = (TILESIZE * SCALE) - (bPos.y - aPos.y);
//     else
//         result.y = (TILESIZE * SCALE) - (aPos.y - bPos.y);
//
//     // if there is no collision, it will return negative values
//     return result;
// }

Vec2 World::getOverlap(Vec2 aPos, Vec2 bPos) {
    Vec2 result = Vec2(-1, -1);

    // X
    if (aPos.x < bPos.x)
        result.x = (TILESIZE * SCALE) - (bPos.x - aPos.x);
    else
        result.x = (TILESIZE * SCALE) - (aPos.x - bPos.x);
    // Y
    if (aPos.y < bPos.y)
        result.y = (TILESIZE * SCALE) - (bPos.y - aPos.y);
    else
        result.y = (TILESIZE * SCALE) - (aPos.y - bPos.y);

    return result;
}

void World::clearEntities() { entities.clear(); }

void World::draw(std::shared_ptr<StateManager> stateManager) {
    std::shared_ptr<Camera> camera = Camera::getInstance();

    std::shared_ptr<Player> player = getPlayer();

    // camera
    camera->update(player, stateManager);

    // entities only if visible
    for (auto& entity : entities) {
        if (camera->entityIsVisible(entity))
            entity->draw();
    }
    player->draw();
}
