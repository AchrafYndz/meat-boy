#include "World.h"
#include "../controller/ConcreteFactory.h"
#include "../controller/StateManager.h"
#include "../util/json.hpp"
#include "Camera.h"
#include "Entity.h"
#include "Player.h"

#include <fstream>
#include <sstream>

std::shared_ptr<Model::World> Model::World::world(new World);

std::shared_ptr<Model::World> Model::World::getInstance() { return world; }

void Model::World::loadLevel(int lvl, std::shared_ptr<Controller::StateManager> stateManager, std::shared_ptr<Camera> camera) {
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
    levelMap.seekg(0);                             // return to the beginning
    camera->setHeight(totalRows);                  // set total height of level
    camera->setCameraCenter(totalRows * tileSize); // set initial camera position

    auto world_ = World::getInstance();
    std::string value;
    int column = 0;                             // top
    int row = 0;                                // left
    while (getline(levelMap, line)) {           /* read entire line into line */
        std::stringstream ss(line);             /* create stringstream from line */
        while (getline(ss, value, delimiter)) { /* read each field from line */
            Vec2 pos = camera->normalizedPosition(Vec2(column * tileSize, row * tileSize));
            if (value == "0")
                world_->addEntity(Controller::ConcreteFactory::getInstance()->CreateObject(Entity::wall, pos));
            else if (value == "1") // goal
                world_->addEntity(Controller::ConcreteFactory::getInstance()->CreateObject(Entity::goal, pos));
            else if (value == "2") // player position
                world_->addEntity(Controller::ConcreteFactory::getInstance()->CreateObject(Entity::player, pos));

            column++;
        }
        row++;
        column = 0;
    }
}

Model::Vec2 Model::World::getOverlap(Model::Vec2 aPos, Model::Vec2 bPos) {
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

bool Model::World::rectContainsPoint(floatRect r, Vec2 point) {
    float minX = std::min(r.left, (r.left + r.width));
    float maxX = std::max(r.left, (r.left + r.width));
    float minY = std::min(r.top, (r.top + r.height));
    float maxY = std::max(r.top, (r.top + r.height));

    return (point.x >= minX) && (point.x < maxX) && (point.y >= minY) && (point.y < maxY);
}

void Model::World::clearEntities() { entities.clear(); }

void Model::World::update(std::shared_ptr<Camera> camera) {
    for (auto entity : entities) {
        entity->update(camera);
    }
}
