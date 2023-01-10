#include "World.h"
#include "../controller/ConcreteFactory.h"
#include "../util/json.hpp"
#include "Camera.h"
#include "Entity.h"
#include "Player.h"

#include <fstream>
#include <sstream>
#include <system_error>

void Model::World::loadLevel(int levelNumber, const std::shared_ptr<Controller::StateManager>& stateManager, const std::shared_ptr<Camera>& camera) {
    clearEntities();

    float tileSize = TILE_SIZE * SCALE;

    std::ifstream levelsInfo("resources/levels/levels-info.json");

    if (!levelsInfo.is_open()) {
        throw std::invalid_argument("Could not open file for levelsInfo");
    }

    nlohmann::json j;
    levelsInfo >> j;

    std::string levelPath = j["level-" + std::to_string(levelNumber)]["filePath"];
    bool autoScrolling = j["level-" + std::to_string(levelNumber)]["autoScrolling"];

    stateManager->goToLevel(levelNumber, autoScrolling);

    std::ifstream levelMap(levelPath);

    if (!levelMap.is_open()) {
        throw std::invalid_argument("Could not open file for levelMap");
    }

    std::string line;
    char delimiter = ',';

    // get amount of rows
    int totalRows = 0;
    while (getline(levelMap, line))
        totalRows++;
    levelMap.clear();
    levelMap.seekg(0);                             // return to the beginning
    camera->setTotalHeight(totalRows);                  // set total height of level
    camera->setCameraHeight(float(totalRows) * tileSize); // set initial camera position

    std::string value;
    int column = 0;                             // top
    int row = 0;                                // left
    while (getline(levelMap, line)) {           /* read entire line into line */
        std::stringstream stringstream(line);             /* create stringstream from line */
        while (getline(stringstream, value, delimiter)) { /* read each field from line */
            floatVector2 pos = camera->normalizePosition(floatVector2(float(column) * tileSize, float(row) * tileSize));
            if (value == "0") // wall
                addEntity(concreteFactory->createEntity(shared_from_this(), Entity::wall, pos));
            else if (value == "1") // goal
                addEntity(concreteFactory->createEntity(shared_from_this(), Entity::goal, pos));
            else if (value == "2") // player
                addEntity(concreteFactory->createEntity(shared_from_this(), Entity::player, pos));

            column++;
        }
        row++;
        column = 0;
    }
}

floatVector2 Model::World::getOverlap(floatVector2 aPosition, floatVector2 bPosition) {
    floatVector2 result = floatVector2(-1, -1);

    // X
    if (aPosition.x < bPosition.x)
        result.x = (TILE_SIZE * SCALE) - (bPosition.x - aPosition.x);
    else
        result.x = (TILE_SIZE * SCALE) - (aPosition.x - bPosition.x);
    // Y
    if (aPosition.y < bPosition.y)
        result.y = (TILE_SIZE * SCALE) - (bPosition.y - aPosition.y);
    else
        result.y = (TILE_SIZE * SCALE) - (aPosition.y - bPosition.y);

    return result;
}

bool Model::World::rectangleContains(floatRectangle rectangle, floatVector2 point) {
    float minX = std::min(rectangle.left, (rectangle.left + rectangle.width));
    float maxX = std::max(rectangle.left, (rectangle.left + rectangle.width));
    float minY = std::min(rectangle.top, (rectangle.top + rectangle.height));
    float maxY = std::max(rectangle.top, (rectangle.top + rectangle.height));

    return (point.x >= minX) && (point.x < maxX) && (point.y >= minY) && (point.y < maxY);
}

void Model::World::clearEntities() { entities.clear(); }

void Model::World::update(const std::shared_ptr<Camera>& camera) {
    for (const auto& entity : entities) {
        entity->update(shared_from_this(), camera);
    }
}
