#include "Misc.h"

bool tToggle = false;
bool bToggle = false;
bool radToggle = false;

Misc *pMisc = new Misc();


void Misc::Radar()
{
	if (GetAsyncKeyState(VK_F10)) // toggle status
	{
		radToggle = !radToggle;
		if (radToggle) std::cout << "Radar ON" << std::endl;
		else std::cout << "Radar OFF" << std::endl;
		SaveCPU(200);
	}

	SaveCPU(1); // Sleeping the Thread for 1 ms to save cpu usage
	if (!radToggle) return; // return if feature isnt toggled

	for (int i = 1; i < 64; i++)
	{
		int dwEntity = m->ReadMem<int>(m->cDll.dwBase + offsets::entityList + i * 0x10); // looping through 64 entitys in the list
		bool dormant = pEntity->getEntityDormantStatus(dwEntity); // getting the entitys dormant status and saving it in our boolean

		if (dormant) continue; // continue if entity is dormant

		int pEntTeam = pEntity->getEntityTeamNum(dwEntity); // getting the entityteamnum and saving it in our integer

		if (pEntTeam == pLocal->getTeamNum()) continue; // continue if the entitys teamnumber equals our localplayers one

		m->WriteMem<int>(dwEntity + offsets::m_bSpotted, true); // writting bspotted to true to achieve a ingameradar
	}
}

void Misc::Bhop()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_F7))
		{
			bToggle = !bToggle;
			if (bToggle) std::cout << "Bhop is ON" << std::endl;
			else std::cout << "Bhop is OFF" << std::endl;
			Sleep(200);
		}
		SaveCPU(1);
		if (!bToggle) continue;
		if (GetAsyncKeyState(VK_SPACE))
		{
			if (!pLocal->InAir())
			{
				m->WriteMem<int>(m->cDll.dwBase + offsets::dwForceJump, 6); // write dwforcejump to 6 in memory to jump, 4-5 with a sleep would work too but 6 is way more accurate
			}
		}
	}
}

void Misc::Trigger()
{
	if (GetAsyncKeyState(VK_F2))
	{
		tToggle = !tToggle;
		if (tToggle) std::cout << "Triggerbot is ON" << std::endl;
		else std::cout << "Triggerbot is OFF" << std::endl;
		SaveCPU(200);
	}

	SaveCPU(1);

	if (!tToggle) return;
	int lInCross = m->ReadMem<int>(pLocal->getLocalPlayer() + offsets::crosshairID) - 1;
	int lTeam = m->ReadMem<int>(pLocal->getLocalPlayer() + offsets::teamNum);
	int vecVel = m->ReadMem<int>(pLocal->getLocalPlayer() + offsets::vecVel);
	DWORD tEntityBase = m->ReadMem<DWORD>(m->cDll.dwBase + offsets::entityList + ((lInCross) * 0x10));
	int tEntityTeam = pEntity->getEntityTeamNum(tEntityBase);
	bool tDormant = pEntity->getEntityDormantStatus(tEntityBase);

	if ((lInCross > 0 && lInCross <= 64) && (tEntityBase != NULL) && (tEntityTeam != lTeam) && (!tDormant) && (vecVel == 0))
	{
		SaveCPU(25);
		m->WriteMem<int>(m->cDll.dwBase + offsets::dwForceAttack, 6);
	}

}