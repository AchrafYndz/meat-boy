#ifndef INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H
#define INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

class Goal : public Entity {
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Goal(int x, int y);

    void update() override;

    void draw() override;

    Vec2 getPosition() override;
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H