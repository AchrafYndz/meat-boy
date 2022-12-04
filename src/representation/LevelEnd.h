#ifndef INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H
#define INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H

#include <SFML/Graphics.hpp>
#include "../logic/Entity.h"

class LevelEnd : public Entity {
private:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    LevelEnd(int x, int y);

    void update() override;

    void draw() override;

    Vec2 getPosition() override;
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H