#include "World.h"

std::unique_ptr<World> World::world(new World);

World* World::getInstance() {
	return world.get();
}

Vec2 World::getOverlap(Vec2 aPos, Vec2 bPos)
{
	Vec2 result = Vec2(-1, -1);

	// X
	if (aPos.x < bPos.x) result.x = TILESIZE * SCALE - (bPos.x - aPos.x);
	else result.x = TILESIZE * SCALE - (aPos.x - bPos.x);
	// Y
	if (aPos.y < bPos.y) result.y = TILESIZE * SCALE - (bPos.y - aPos.y);
	else result.y = TILESIZE * SCALE - (aPos.y - bPos.y);

	// if there is no collision, it will return negative values
	return result;
}
