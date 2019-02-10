#include "Visuals.h"

bool fToggle = false;
bool gToggle = false;
bool cToggle = false;
float flashopacity = 255.f; // may need to be moved back to main.cpp

Visuals *pVisuals = new Visuals();

void Visuals::GlowESP()
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

	static DWORD objGlowArray = 0; // declare the static dword
	static int objCount = 0; // declare static integer

	objGlowArray = m->ReadMem<DWORD>(m->cDll.dwBase + offsets::dwGlow); // Getting the dwGlowObject Array
	objCount = m->ReadMem<DWORD>(m->cDll.dwBase + offsets::dwGlow + 0x4); // Getting the object count its similar to the entity list loop

	if (objGlowArray == 0) return; // return when objGlowArray equals 0

	for (int i = 1; i < objCount; i++) // scanning through the object count
	{
		DWORD mObj = objGlowArray + i * sizeof(glow_t);
		glow_t vGlowObj = m->ReadMem<glow_t>(mObj);

		if (!vGlowObj.dwBase)
			continue;

		if (pEntity->getHealth(vGlowObj.dwBase) <= 0) continue; // fixed glowing non existing CCSPlayer entitys

		if (pEntity->getEntityDormantStatus(vGlowObj.dwBase)) continue; // if dormant continue

		if (!pEntity->getClassID(vGlowObj.dwBase) == 38) continue; // Player is 38 now thx nci love u // CCSPlayer(DT_CSPlayer):110 1709 == 38

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

void Visuals::Chams()
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

void Visuals::noFlash()
{
	if (GetAsyncKeyState(VK_F5))
	{
		fToggle = !fToggle;
		if (fToggle) std::cout << "No Flash is ON" << std::endl;
		else std::cout << "No Flash is OFF" << std::endl;
		SaveCPU(200);
	}
	SaveCPU(1);
	if (!fToggle && flashopacity == 0.f) // added this flashopacity check so we dont call the writememory down below all the time if the feature isnt enabled
	{
		m->WriteMem<float>(pLocal->getLocalPlayer() + offsets::flashAlpha, 255.f); // reseting the glow alpha level in memory that we wrote incase we deactivate the feature
		flashopacity = 255.f; // setting flashopcatiy to 255.f to prevent further recalling of the writememory
		return; // return
	}
	if (fToggle)
	{
		if (m->ReadMem<float>(pLocal->getLocalPlayer() + offsets::flashAlpha) > 0.0f)
		{
			m->WriteMem<float>(pLocal->getLocalPlayer() + offsets::flashAlpha, 0.0f); // actual no flash we're setting the flashalpha float value to 0 to achieve "no flash"
			flashopacity = 0.f; // setting flashopacity to zero for above if statement
		}
	}
}