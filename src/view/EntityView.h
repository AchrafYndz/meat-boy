#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H

#include <memory>

#include "../model/ObserverPattern.h"

#include <SFML/Graphics.hpp>

struct Vec2;

class EntityView : public Observer {
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	EntityView(std::string filename);
	~EntityView() override {  }

	void update(int x, int y) override {
		sprite.setPosition(x, y);
	}

	Vec2 size();

	void face(bool left);
	void draw(Vec2 pos);
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H
