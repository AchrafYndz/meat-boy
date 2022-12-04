#ifndef INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H
#define INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H

#include <SFML/Graphics.hpp>
#include "../logic/Entity.h"
#include "../logic/World.h"

#include <memory>

class Player : public Entity {
private:
    Player();

    static std::unique_ptr<Player> player;

    sf::Texture texture;
    sf::Sprite sprite;

    struct Sensor {
        int x;
        int y;
        bool active = false;
    };
    Sensor leftSensor;
    Sensor rightSensor;
    Sensor bottomSensor;

    enum PlyState {
        none, standingOnTile, onAir, onLeftWall, onRightWall
    };
    PlyState state = PlyState::onAir;

    const float acceleration = 0.8f;
    float currentAcceleration = 0.f;
    const float topSpeed = 5.f;

    const float JUMPING_TOTAL_TIME = 0.4f;
    float currentJumpingTime = 0.f;

    enum JumpType {
        normal, toTheLeft, toTheRight
    };
    JumpType jumpType;
public:
    Player(Player &other) = delete;

    void operator=(const Player &other) = delete;

    static Player *getInstance();

    void processInput();

    void update() override;

    void draw() override;

    Vec2 getPosition() override;

    void setInitialPosition(int x, int y);
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_PLAYER_H