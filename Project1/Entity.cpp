#include "Entity.h"

Entity *pEntity = new Entity();

Entity::Entity() {} // defining constructor because we can
Entity::~Entity() {} // defining destructor because we can

int Entity::getEntityTeamNum(int EntityList) // getting the entity teamnum by feeding it the current looped list
{
	return m->ReadMem<int>(EntityList + offsets::teamNum);
}

bool Entity::getEntityDormantStatus(int EntityList) // getting the entity dormant status via the current looped list
{
	return m->ReadMem<bool>(EntityList + offsets::bDormant);
}