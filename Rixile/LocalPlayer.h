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
	int getMoveType();
	bool InAir();
	void ForceFullUpdate();

};

extern LocalPlayer *pLocal;