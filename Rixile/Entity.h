#pragma once
#include "Includes.h"

class Entity
{
public:
	Entity();
	~Entity();

	int getEntityTeamNum(int EntityList);
	bool getEntityDormantStatus(int EntityList);
	int getClassID(int entity);
	int getHealth(int entity);

};
extern Entity *pEntity;