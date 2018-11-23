#pragma once
#include "Includes.h"

class LocalPlayer
{
public:
	~LocalPlayer();
	LocalPlayer();
	DWORD getLocalPlayer();
	int getTeamNum();
	int getFlags();

};

extern LocalPlayer *pLocal;