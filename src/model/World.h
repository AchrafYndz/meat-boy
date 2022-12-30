#ifndef INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H
#define INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H

#include "../controller/StateManager.h"
#include <memory>
#include <vector>

namespace Model {
class Entity;
class Player;
class Camera;

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
    World() = default;

    static std::shared_ptr<World> world;

    std::vector<std::shared_ptr<Entity>> entities;

    std::shared_ptr<Player> player;

public:
    World(World& other) = delete;

    struct floatRect {
        float left;
        float top;
        float width;
        float height;
    };

    void operator=(const World& other) = delete;

    static std::shared_ptr<World> getInstance();

    // Load a Level
    void loadLevel(int lvl, const std::shared_ptr<Controller::StateManager>& stateManager, const std::shared_ptr<Camera>& camera);

    static Vec2 getOverlap(Vec2 aPos, Vec2 bPos);

    static bool rectContainsPoint(floatRect r, Vec2 point);

    void addEntity(const std::shared_ptr<Entity>& e) { entities.push_back(e); }

    std::vector<std::shared_ptr<Entity>> getEntities() { return entities; }

    std::shared_ptr<Player> getPlayer() { return player; };

    void setPlayer(std::shared_ptr<Player>& player_) { player = player_; }

    void clearEntities();

    void update(const std::shared_ptr<Camera>& camera);
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H
