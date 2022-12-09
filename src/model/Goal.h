#ifndef INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H
#define INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H

#include "Entity.h"
#include "../view/EntityView.h"
#include <SFML/Graphics.hpp>

class Goal : public Entity {
public:
    Goal(Vec2 pos);
	~Goal() {}

    void update() override;

	void draw() override;
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H