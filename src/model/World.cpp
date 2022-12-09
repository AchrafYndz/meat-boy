#include "World.h"
#include "Camera.h"
#include "Entity.h"
#include "Player.h"
#include "ConcreteFactory.h"
#include "../controller/StateManager.h"
#include "../util/json.hpp"

#include <fstream>
#include <sstream>

std::shared_ptr<World> World::world(new World);

World::World() {}

std::shared_ptr<World> World::getInstance() { return world; }

void World::loadLevel(int lvl)
{
	clearEntities();

	//addEntity(Player::getInstance());

	int tileSize = TILESIZE * SCALE;

	std::ifstream levelMap;
	std::ifstream levelsInfo("resources/levels/levels-info.json");

	nlohmann::json j;
	levelsInfo >> j;

	std::string lvlPath = j["level-" + std::to_string(lvl)]["filePath"];
	bool autoScrolling = j["level-" + std::to_string(lvl)]["autoScrolling"];

	StateManager::getInstance()->goToLevel(lvl, autoScrolling);

	levelMap.open(lvlPath);

	std::string line;
	char delimiter = ',';

	std::string value;
	int column = 0;                             // top
	int row = 0;                                // left
	while (getline(levelMap, line)) {           /* read entire line into line */
		std::stringstream ss(line);             /* create stringstream from line */
		while (getline(ss, value, delimiter)) { /* read each field from line */
			Vec2 pos(column * tileSize, row * tileSize);
			if (value == "0")
				World::getInstance()->addEntity(ConcreteFactory::getInstance()->CreateObject(Entity::wall, pos));
			else if (value == "1") // goal
				World::getInstance()->addEntity(ConcreteFactory::getInstance()->CreateObject(Entity::goal, pos));
			else if (value == "2") // player position
				Player::getInstance()->startLevel(pos.x, pos.y);

			column++;
		}
		row++;
		column = 0;
	}

	// set initial camera position
	Camera::getInstance()->setCameraCenter(row * tileSize);
}

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

    // if there is no collision, it will return negative values
    return result;
}

void World::clearEntities() {
   entities.clear();
}

void World::draw() {
	std::shared_ptr<Camera> camera = Camera::getInstance();

	// camera
	camera->update(Player::getInstance());

	// entities only if visible
    for (auto& entity : entities) {
        if (camera->entityIsVisible(entity))
            entity->draw();
    }
	Player::getInstance()->draw();
}
