#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H

struct Vec2;

class Entity {
private:
public:
	enum Type { none, player, wall, end };
	Type type = none;

	Entity(Type t) { type = t; }
	Type getType() const { return type; }

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual Vec2 getPosition() = 0;
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ENTITY_H