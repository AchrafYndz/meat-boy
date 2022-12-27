#ifndef INC_2022_PROJECT_ACHRAFYNDZ_WALL_H
#define INC_2022_PROJECT_ACHRAFYNDZ_WALL_H

#include "ObserverPattern.h"
#include "Entity.h"

struct Vec2;

class Wall : public Entity, public Subject {
public:
    Wall(Vec2 pos);
	~Wall() {}

	void update(std::shared_ptr<Camera> camera) override;
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_WALL_H