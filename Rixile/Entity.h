#pragma once
#include "Includes.h"

class Entity
{
public:
	Entity();
	~Entity();

	int getEntityTeamNum(int EntityList);
	bool getEntityDormantStatus(int EntityList);

};
extern Entity *pEntity;