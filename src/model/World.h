#ifndef INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H
#define INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H

#include "../controller/ConcreteFactory.h"
#include "../controller/StateManager.h"
#include "../util/floatRectangle.h"
#include <memory>
#include <vector>

namespace Model {
class Entity;
class Player;
class Camera;

class World : public std::enable_shared_from_this<World> {
private:
    std::vector<std::shared_ptr<Entity>> entities;

    std::shared_ptr<Controller::ConcreteFactory> concreteFactory = std::make_shared<Controller::ConcreteFactory>();

    std::shared_ptr<Player> player;

public:
    World() = default;


    // Load a Level
    void loadLevel(int levelNumber, const std::shared_ptr<Controller::StateManager>& stateManager, const std::shared_ptr<Camera>& camera);

    static floatVector2 getOverlap(floatVector2 aPosition, floatVector2 bPosition);

    static bool rectangleContains(floatRectangle rectangle, floatVector2 point);

    void addEntity(const std::shared_ptr<Entity>& entity) { entities.push_back(entity); }

    std::vector<std::shared_ptr<Entity>> getEntities() { return entities; }

    std::shared_ptr<Player> getPlayer() { return player; };

    void setPlayer(std::shared_ptr<Player>& player_) { player = player_; }

    void clearEntities();

    void update(const std::shared_ptr<Camera>& camera);
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H
