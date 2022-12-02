#ifndef INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H
#define INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H

#include <memory>
#include <vector>

class Entity;

//Constants
const float TILESIZE = 256;
const float SCALE = 0.125;

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

    static std::unique_ptr<World> world;

    std::vector<Entity *> entities;
public:
    World(World &other) = delete;

    void operator=(const World &other) = delete;

    static World *getInstance();

    // collisions
    Vec2 getOverlap(Vec2 aPos, Vec2 bPos);

    void addEntity(Entity *e) { entities.push_back(e); }

    std::vector<Entity *> getEntities() { return entities; }

    void drawAll();
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H
