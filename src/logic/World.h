#ifndef INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H
#define INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H

#include <memory>

class Entity;

//Constants
const float TILESIZE = 256;
const float SCALE = 0.125;
// Vector
struct Vec2 {
	float x;
    float y;
	Vec2() { x = 0.0f; y = 0.0f; }
	Vec2(float _x, float _y) { x = _x; y = _y; }
};

class World {
private:
	World() = default;
	static std::unique_ptr<World> world;

public:
	World(World& other) = delete;

	void operator=(const World& other) = delete;

	static World* getInstance();
	
	Vec2 getOverlap(Vec2 aPos, Vec2 bPos);
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_WORLD_H
