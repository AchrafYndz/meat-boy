#ifndef INC_2022_PROJECT_ACHRAFYNDZ_WALL_H
#define INC_2022_PROJECT_ACHRAFYNDZ_WALL_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

struct Vec2;

class Wall : public Entity {
public:
    Wall(Vec2 pos);
	~Wall() {}

	void draw() override;
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_WALL_H