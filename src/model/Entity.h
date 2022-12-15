#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H

#include <memory>

#include "World.h"

#include <SFML/Graphics.hpp>

class EntityView;

class Entity {
protected:
	std::shared_ptr<EntityView> observer;

	Vec2 position; // normalized position

	sf::Texture texture;
	sf::Sprite sprite;
public:
    enum Type { none, player, wall, goal };
    Type type = none;

    Entity(Type t) { type = t; }
	virtual ~Entity() { }

	void attachObserver(std::shared_ptr<EntityView> o) { observer = o; }

    Type getType() const { return type; }

	virtual void draw() = 0;

	Vec2 getPosition() { return position; }
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H