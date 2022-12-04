#ifndef INC_2022_PROJECT_ACHRAFYNDZ_WALL_H
#define INC_2022_PROJECT_ACHRAFYNDZ_WALL_H

#include <SFML/Graphics.hpp>
#include "../logic/Entity.h"

struct Vec2;

class Wall : public Entity {
private:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Wall(Vec2 p);

    void update() override {}

    void draw() override;

    Vec2 getPosition() override;
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_WALL_H