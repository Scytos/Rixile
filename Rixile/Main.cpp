#include "Includes.h"
#include "LocalPlayer.h"
#include "Entity.h"

// Credits to my sidehoe nci* love ya

////////////////////////////////////////////////////////
/////////moving the stuff below at a later date////////
bool bToggle = false;
bool tToggle = false;
bool fToggle = false;
bool gToggle = false;
bool vgToggle = false;
bool aToggle = false;
bool rToggle = false;
bool cToggle = false;
bool radToggle = false;
bool fovToggle = false;

typedef struct {
	float x, y, z;
}Vector;

struct Color
{
	BYTE r;
	BYTE g;
	BYTE b;
	BYTE a;
};

struct glow_t {
	DWORD dwBase;
	float r;
	float g;
	float b;
	float m_flGlowAlpha;
	char m_unk[4];
	float m_flUnk;
	float m_flBloomAmount;
	float m_flUnk1;
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	bool m_bFullBloomRender;
	char m_unk1;
	int m_nFullBloomStencilTestValue;
	int m_nGlowStyle;
	int m_nSplitScreenSlot;
	int m_nNextFreeSlot;
};
//////////////////////////////////////////////////

void radar()
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

void chams()
{
	if (GetAsyncKeyState(VK_F9)) // toggle status
	{
		cToggle = !cToggle;
		if (cToggle) std::cout << "Chams ON" << std::endl;
		else std::cout << "Chams OFF" << std::endl;
		SaveCPU(200);
	}
	Color obj; // Defining the color struct
	SaveCPU(1);
	if (!cToggle) return; // return if feature isnt toggled
	for (int i = 1; i < 64; i++)
	{
		int dwEntity = m->ReadMem<int>(m->cDll.dwBase + offsets::entityList + i * 0x10); 
		bool dormant = pEntity->getEntityDormantStatus(dwEntity);

		if (dormant) continue; 

		int pEntTeam = pEntity->getEntityTeamNum(dwEntity);

		if (pEntTeam == pLocal->getTeamNum()) continue;

		obj.r = 45; // setting the red color here
		obj.g = 4; // green here
		obj.b = 86; // blue here
		obj.a = 255; // alpha here

		m->WriteMem<Color>(dwEntity + 0x70, obj); // writing the object
	}
}

void noFlash()
{
	if (GetAsyncKeyState(VK_F5))
	{
		fToggle = !fToggle;
		if(fToggle) std::cout << "No Flash is ON" << std::endl;
		else std::cout << "No Flash is OFF" << std::endl;
		SaveCPU(200);
	}
	SaveCPU(1);
	if (!fToggle)
	{
		m->WriteMem<float>(pLocal->getLocalPlayer() + offsets::flashAlpha, 255.f); // reseting the glow alpha level in memory that we wrote incase we deactivate the feature
		return; // return
	}
	if (m->ReadMem<float>(pLocal->getLocalPlayer() + offsets::flashAlpha) > 0.0f) m->WriteMem<float>(pLocal->getLocalPlayer() + offsets::flashAlpha, 0.0f); // actual no flash we're setting the flashalpha float value to 0 to achieve "no flash"
}

void Glow() // This is a more proper method of doing a glowesp and a more natural one, doing it via entitylist is for sillys
{
	if (GetAsyncKeyState(VK_F3))
	{
		gToggle = !gToggle;
		if (gToggle) std::cout << "Glow is ON" << std::endl;
		else std::cout << "Glow is OFF" << std::endl;
		SaveCPU(200);
	}

	SaveCPU(1);
	if (!gToggle) return;

	static DWORD objGlowArray = 0; // emptying glowarray
	static int objCount = 0; // emptying objcount

	objGlowArray = m->ReadMem<DWORD>(m->cDll.dwBase + offsets::dwGlow); // Getting the dwGlowObject Array
	objCount = m->ReadMem<DWORD>(m->cDll.dwBase + offsets::dwGlow + 0x4); // Getting the object count its similar to the entity list loop

	if (objGlowArray == 0) return;

	for (int i = 1; i < objCount; i++) // scanning through the object count
	{
		DWORD mObj = objGlowArray + i * sizeof(glow_t);
		glow_t vGlowObj = m->ReadMem<glow_t>(mObj);

		if (pEntity->getHealth(vGlowObj.dwBase) <= 0) continue; // fixed glowing non existing CCSPlayer entitys

		if (pEntity->getEntityDormantStatus(vGlowObj.dwBase)) continue; // if dormant continue

		if (!pEntity->getClassID(vGlowObj.dwBase) == 35) continue; // we break out of the loop if the entity is not a player // CCSPlayer(DT_CSPlayer):110 1709 == 35

		vGlowObj.r = .176f; // setting Red color in glow
		vGlowObj.m_flGlowAlpha = 1.f; // setting Alpha in glow
		vGlowObj.g = .015f; // setting green color in glow
		vGlowObj.b = .337f; // setting blue color in glow
		vGlowObj.m_bRenderWhenOccluded = true; // writing that to true so glow will show through tha walls
		vGlowObj.m_bRenderWhenUnoccluded = false;
		vGlowObj.m_bFullBloomRender = false;
		vGlowObj.m_nGlowStyle = 0; // Standard glowstyle


		m->WriteMem(mObj, vGlowObj); // writing our object
	}
	
}

void Bhop()
{
	if (GetAsyncKeyState(VK_F7))
	{
		bToggle = !bToggle;
		if (bToggle) std::cout << "Bhop is ON" << std::endl;
		else std::cout << "Bhop is OFF" << std::endl;
		Sleep(200);
	}
	SaveCPU(1);
	if (!bToggle) return;
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (!pLocal->InAir() && pLocal->getMoveType() != 9) // 9 is the movetypeladder so we can jump of ladders
		{
            m->WriteMem<int>(m->cDll.dwBase + offsets::dwForceJump, 6); // write dwforcejump to 6 in memory to jump 4-5 with a sleep would work too but 6 is way more accurate
		}
	}
}


void Trigger()
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

void updateOffsets()
{
	// A little word to the pattern scanning
	// The FindPatternArray works like this you add the mask first and then you have another digit after it for the localplayer array its a 19, thats the count of the mask length and after that its the actual signature.

	DWORD LocalPlayerArray = m->FindPatternArray(m->cDll.dwBase, m->cDll.dwSize, "xxx????xx????xxxxx?", 19, 0x8D, 0x34, 0x85, 0x0, 0x0, 0x0, 0x0, 0x89, 0x15, 0x0, 0x0, 0x0, 0x0, 0x8B, 0x41, 0x8, 0x8B, 0x48, 0x0);
	offsets::localPlayer = m->ReadMem<DWORD>(LocalPlayerArray + 3) + m->ReadMem<BYTE>(LocalPlayerArray + 18) - m->cDll.dwBase;
	DWORD EntityListArray = m->FindPatternArray(m->cDll.dwBase, m->cDll.dwSize, "x????xx?xxx", 11, 0x5, 0x0, 0x0, 0x0, 0x0, 0xC1, 0xE9, 0x0, 0x39, 0x48, 0x4);
	offsets::entityList = (m->ReadMem<DWORD>(EntityListArray + 1) + m->ReadMem<BYTE>(EntityListArray + 7)) - m->cDll.dwBase;
	DWORD ForceJumpArray = m->FindPatternArray(m->cDll.dwBase, m->cDll.dwSize, "xx????xxxxxxx", 13, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xD6, 0x8B, 0xC1, 0x83, 0xCA, 0x02);
	offsets::dwForceJump = m->ReadMem<DWORD>(ForceJumpArray + 2) - m->cDll.dwBase;
	DWORD ForceAttackArray = m->FindPatternArray(m->cDll.dwBase, m->cDll.dwSize, "xx????xx????xxxxxxx", 19, 0x89, 0x0D, 0x0, 0x0, 0x0, 0x0, 0x8B, 0x0D, 0x0, 0x0, 0x0, 0x0, 0x8B, 0xF2, 0x8B, 0xC1, 0x83, 0xCE, 0x04);
	offsets::dwForceAttack = m->ReadMem<DWORD>(ForceAttackArray + 2) - m->cDll.dwBase;
	DWORD ClientStateArray = m->FindPatternArray(m->eDll.dwBase, m->eDll.dwSize, "x????xxxxxxxxxx", 15, 0xA1, 0x0, 0x0, 0x0, 0x0, 0x33, 0xD2, 0x6A, 0x0, 0x6A, 0x0, 0x33, 0xC9, 0x89, 0xB0);
	offsets::dwClientState = m->ReadMem<DWORD>(ClientStateArray + 1) - m->eDll.dwBase;
	DWORD GlowObjectArray = m->FindPatternArray(m->cDll.dwBase, m->cDll.dwSize, "x????xxxx", 9, 0xA1, 0x0, 0x0, 0x0, 0x0, 0xA8, 0x01, 0x75, 0x4B);
	offsets::dwGlow = m->ReadMem<DWORD>(GlowObjectArray + 1) + 0x4 - m->cDll.dwBase;
	DWORD ClientState_ViewAnglesArray = m->FindPatternArray(m->eDll.dwBase, m->eDll.dwSize, "xxx????xxxxx", 13, 0xF3, 0x0F, 0x11, 0x80, 0x0, 0x0, 0x0, 0x0, 0xD9, 0x46, 0x04, 0xD9, 0x05);
	offsets::dwClientState_ViewAngles = m->ReadMem<DWORD>(ClientState_ViewAnglesArray + 4);
}

int main()
{
	std::cout << "Elixir Free made by nci and overhauled by IcePixel" << std::endl;
	PrintOffsetsConsole("Client Base Address: 0x", m->cDll.dwBase);
	std::cout << "Pattern Scanning...\n" << std::endl;
	updateOffsets();
	PrintOffsetsConsole("Glow Pointer: 0x", offsets::dwGlow); 
	PrintOffsetsConsole("Local Player: 0x", offsets::localPlayer);
	PrintOffsetsConsole("Entity List: 0x", offsets::entityList);
	PrintOffsetsConsole("Client State: 0x", offsets::dwClientState);
	PrintOffsetsConsole("ForceJump: 0x", offsets::dwForceJump);
	PrintOffsetsConsole("ForceAttack: 0x", offsets::dwForceAttack);
	PrintOffsetsConsole("CState Viewangles: 0x", offsets::dwClientState_ViewAngles);

	std::cout << "\n";
	std::cout << "Trigger is VK_F2 \n";
	std::cout << "Glow is VK_F3 \n";
	std::cout << "No Flash is VK_F5 \n";
	std::cout << "Bhop is VK_F7 \n";
	std::cout << "Chams is VK_F9 \n";
	std::cout << "Radar is VK_F10 \n";
	std::cout << "\n";
	while (true)
	{
		Trigger();
		Bhop();
		Glow();
		chams();
		radar();
		noFlash();
	}
	delete m;
	return 0;
}

//uncommented stuff

/*void RCS()
{
if (GetAsyncKeyState(VK_F8))
{
rToggle = !rToggle;
if (rToggle) std::cout << "RCS ON" << std::endl;
else std::cout << "RCS OFF" << std::endl;
Sleep(200);
}
if (!rToggle) return;

DWORD ClientState;
DWORD pLocalPlayer;
int pShotsFired;
Vector CurrentViewAngles;
Vector vPunch;
Vector NewViewAngles;
Vector OldAimPunch;
Vector random;
OldAimPunch.x = OldAimPunch.y = OldAimPunch.z = 0;

pLocalPlayer = m->ReadMem<DWORD>(m->cDll.dwBase + offsets::localPlayer);
vPunch = m->ReadMem<Vector>(pLocalPlayer + offsets::m_viewPunchAngle);
pShotsFired = m->ReadMem<int>(pLocalPlayer + offsets::m_iShotsFired);

if (pShotsFired > 1)
{
ClientState = m->ReadMem<DWORD>(m->cDll.dwBase + offsets::dwClientState);
CurrentViewAngles = m->ReadMem<Vector>(ClientState + offsets::dwClientState_ViewAngles);

NewViewAngles.x = ((CurrentViewAngles.x + OldAimPunch.x) - (vPunch.x * 2.f));
NewViewAngles.y = ((CurrentViewAngles.y + OldAimPunch.y) - (vPunch.y * 2.f));
NewViewAngles.z = 0;

SaveCPU(1);
}

}*/


/*void visGlow()
{
	//This is a shitty way todo a glowesp gonna rework that when I have time
	if (GetAsyncKeyState(VK_F4))
	{
		vgToggle = !vgToggle;
		if (vgToggle) std::cout << "Visible Glow is ON" << std::endl;
		else std::cout << "Visible Glow is OFF" << std::endl;
		SaveCPU(200);
	}
	DWORD gPointer = m->ReadMem<DWORD>(m->cDll.dwBase + offsets::dwGlow);
	DWORD dwPla = m->ReadMem<DWORD>(m->cDll.dwBase + offsets::localPlayer);
	int lTeam = m->ReadMem<int>(dwPla + offsets::teamNum);
	if (!vgToggle) return;
	for (int i = 1; i < 64; i++)
	{
		int pEntity = m->ReadMem<int>(m->cDll.dwBase + offsets::entityList + i * 0x10);
		int pEntIdx = m->ReadMem<int>(pEntity + offsets::dwGlowIdx);

		int pEntTeam = m->ReadMem<int>(pEntity + offsets::teamNum);
		bool dormant = m->ReadMem<int>(pEntity + offsets::bDormant);

		if (dormant) continue;
		if (lTeam == pEntTeam) continue;

		glow_t vGlowObj = m->ReadMem<glow_t>(gPointer + (pEntIdx * 0x38));
		vGlowObj.r = .176f;
		vGlowObj.m_flGlowAlpha = 1.f;
		vGlowObj.g = .015f;
		vGlowObj.b = .337f;
		vGlowObj.m_bRenderWhenOccluded = false;
		vGlowObj.m_bRenderWhenUnoccluded = true;
		vGlowObj.m_nGlowStyle = 1;


		m->WriteMem(gPointer + (pEntIdx * 0x38), vGlowObj);
		SaveCPU(1);
	}
}*/

/*
void fovChanger()
{
if (GetAsyncKeyState(VK_NUMPAD1))
{
fovToggle = !fovToggle;
if (fovToggle) std::cout << "FOV Changer is ON" << std::endl;
else std::cout << "FOV Changer is OFF" << std::endl;
SaveCPU(200);
}
SaveCPU(1);
if (!fovToggle)
{
return;
}

int isScoped = m->ReadMem<int>(pLocal->getLocalPlayer() + offsets::isScoped); // checking if localplayer is scoped

if(isScoped == 0)m->WriteMem<int>(pLocal->getLocalPlayer() + offsets::m_iFOVStart-4, 110);
else if (isScoped > 0) m->WriteMem<int>(pLocal->getLocalPlayer() + offsets::m_iFOVStart - 4, 90);
}
*/