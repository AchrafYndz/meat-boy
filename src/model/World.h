#ifndef INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H
#define INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H

#include <memory>
#include <vector>

class Entity;

// Constants
const float TILESIZE = 256;
// SCALE for 480p
const float SCALE = 0.125;
// SCALE for 720p
// const float SCALE = 0.1875;

// Vector
struct Vec2 {
    float x;
    float y;

    Vec2() {
        x = 0;
        y = 0;
    }

    Vec2(float _x, float _y) {
        x = _x;
        y = _y;
    }
};

class World {
private:
    World();

    static std::shared_ptr<World> world;

    std::vector<std::shared_ptr<Entity>> entities;

public:
    World(World& other) = delete;

    void operator=(const World& other) = delete;

    static std::shared_ptr<World> getInstance();

	// Load a Level
	void loadLevel(int lvl);

    Vec2 getOverlap(Vec2 aPos, Vec2 bPos);

    void addEntity(const std::shared_ptr<Entity>& e) { entities.push_back(e); }

    std::vector<std::shared_ptr<Entity>> getEntities() { return entities; }

    void clearEntities();

    void draw();
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H
