#include "LocalPlayer.h"

LocalPlayer *pLocal = new LocalPlayer();

LocalPlayer::LocalPlayer() {} // defining constructor because we can
LocalPlayer::~LocalPlayer() {} // defining destructor because we can

DWORD LocalPlayer::getLocalPlayer() // getting the localplayer
{
	return m->ReadMem<DWORD>(m->cDll.dwBase + offsets::localPlayer);
}

int LocalPlayer::getTeamNum() // getting the teamnum via our localplayer
{
	return m->ReadMem<int>(pLocal->getLocalPlayer() + offsets::teamNum);
}

int LocalPlayer::getFlags()
{
	return m->ReadMem<int>(pLocal->getLocalPlayer() + 0x100);
}