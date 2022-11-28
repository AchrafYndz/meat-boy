#include "EntityMgr.h"

std::unique_ptr<EntityMgr> EntityMgr::entityMgr(new EntityMgr);

EntityMgr* EntityMgr::getInstance() {
	return entityMgr.get();
}

void EntityMgr::drawAll() {
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->draw();
	}
}
