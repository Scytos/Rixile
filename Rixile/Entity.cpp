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

int Entity::getClassID(int entity) // getting classid for various things example checking for players
{
	DWORD dwClientNetworkable = m->ReadMem<int>(entity + 0x8); // IClientNetworkable VTABLE Location
	DWORD dwGetClientClassFn = m->ReadMem<int>(dwClientNetworkable + 2 * 0x4); // Third function in the vtable /GetClientClass/
    DWORD dwEntityClientClass = m->ReadMem<int>(dwGetClientClassFn + 1); //pointer to ClientClass struct
	
	return m->ReadMem<int>(dwEntityClientClass + 0x14); // actual class id
}

int Entity::getHealth(int entity) // getting entitys health
{
	return  m->ReadMem<int>(entity + 0xFC);
}
