#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H

#include <memory>

#include "../controller/Game.h"
#include "../model/Camera.h"
#include "../model/ObserverPattern.h"

#include <iostream>

#include <SFML/Graphics.hpp>

struct Vec2;

class EntityView : public Observer {
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	EntityView(std::string filename);
	~EntityView() override {  }

	void update(int x, int y, std::shared_ptr<Camera> camera, bool facingLeft = false) override {
        if (camera->entityIsVisible(y)) {
            sprite.setPosition(x, y);
            face(facingLeft);
            Game::getWindow()->draw(sprite);
        }
	}

	Vec2 size();

	void face(bool left);
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H
