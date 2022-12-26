#ifndef INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H
#define INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H

#include "ObserverPattern.h"
#include "Entity.h"
#include "../view/EntityView.h"

class Goal : public Entity, public Subject {
public:
    Goal(Vec2 pos);
	~Goal() {}

	void update() override;
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_LVLEND_H