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
/**
 * The World class is responsible for maintaining the game state and
 * updating the entities. It inherits from std::enable_shared_from_this<World>,
 * so it's possible to pass a shared pointer of the class directly to the methods
 * that are called within this class.
 */
class World : public std::enable_shared_from_this<World> {
private:
    /** A vector of shared pointers to the entities that are in the world */
    std::vector<std::shared_ptr<Entity>> entities;

    /** A shared pointer tot the concrete factory class */
    std::shared_ptr<Controller::ConcreteFactory> concreteFactory = std::make_shared<Controller::ConcreteFactory>();

    /** A shared pointer to the player class */
    std::shared_ptr<Player> player;

public:
    /**
     *  Default Constructor for the Game class
     */
    World() = default;

    /**
     * Load a Level
     * @param levelNumber: int, representing the level number to load
     * @param stateManager: shared_ptr of the current state manager object
     * @param camera: shared_ptr of the current camera object
     */
    void loadLevel(int levelNumber, const std::shared_ptr<Controller::StateManager>& stateManager,
                   const std::shared_ptr<Camera>& camera);

    /**
     * Get the overlap between two rectangles
     * @param aPosition: position of rectangle A
     * @param bPosition: position of rectangle B
     * @return floatVector2 of the overlapped area
     */
    static floatVector2 getOverlap(floatVector2 aPosition, floatVector2 bPosition);

    /**
     * Check if a point is inside a rectangle
     * @param rectangle: the rectangle
     * @param point: the point to check
     * @return bool: whether the point is inside the rectangle or not
     */
    static bool rectangleContains(floatRectangle rectangle, floatVector2 point);

    /**
     * Add an entity to the world
     * @param entity: shared_ptr of the entity to add
     */
    void addEntity(const std::shared_ptr<Entity>& entity) { entities.push_back(entity); }

    /**
     * Get the list of entities in the world
     * @return vector of shared_ptr of entities
     */
    std::vector<std::shared_ptr<Entity>> getEntities() { return entities; }

    /**
     * Get a shared pointer to the player
     * @return shared_ptr of player
     */
    std::shared_ptr<Player> getPlayer() { return player; };

    /**
     *  Adds the player pointer to the world
     *  @param player_ shared_ptr of player to add
     */
    void setPlayer(std::shared_ptr<Player>& player_) { player = player_; }

    /**
     *  Clears the vector of shared_ptrs of entities
     */
    void clearEntities();

    /**
     *  Updates all the entities stored in the world
     *  @param camera game's camera
     */
    void update(const std::shared_ptr<Camera>& camera);
};
} // namespace Model

#endif // INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H
