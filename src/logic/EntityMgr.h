#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ENTITYMGR_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ENTITYMGR_H

#include <memory>
#include <vector>
#include "Entity.h"

class EntityMgr {
private:
	EntityMgr() = default;
	static std::unique_ptr<EntityMgr> entityMgr;

	std::vector<Entity*> entities;
public:
	EntityMgr(EntityMgr& other) = delete;
	void operator=(const EntityMgr& other) = delete;
	static EntityMgr* getInstance();

	void addEntity(Entity* e) { entities.push_back(e); }
	std::vector<Entity*> getEntities() { return entities; }

	void drawAll();
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ENTITYMGR_H
