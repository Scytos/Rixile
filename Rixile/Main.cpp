#include "Includes.h"
#include "Visuals.h"
#include "Misc.h"
// Credits to my sidehoe nci* love ya
int main()
{
	PrintConsole("Elixir Free made by nci and overhauled by IcePixel");
	PrintConsole("Everyone who sees this copy the thing below and paste it in a reply under the rixile thread ;)");
	PrintConsole("696c6f76656e636969776f756c647375636b6869736469636b616c6c646179");
	PrintOffsetsConsole("Client Base Address: 0x", m->cDll.dwBase);
	PrintConsole("Pattern Scanning...\n");
	updateOffsets();
	PrintOffsetsConsole("Glow Pointer: 0x", offsets::dwGlow); 
	PrintOffsetsConsole("Local Player: 0x", offsets::localPlayer);
	PrintOffsetsConsole("Entity List: 0x", offsets::entityList);
	PrintOffsetsConsole("Client State: 0x", offsets::dwClientState);
	PrintOffsetsConsole("ForceJump: 0x", offsets::dwForceJump);
	PrintOffsetsConsole("ForceAttack: 0x", offsets::dwForceAttack);
	PrintOffsetsConsole("CState Viewangles: 0x", offsets::dwClientState_ViewAngles);

	//Starting to implement Multithreading
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)pMisc->Bhop, 0, 0, 0);

	std::cout << "\n";
	std::cout << "Trigger is VK_F2 \n";
	std::cout << "Glow is VK_F3 \n";
	std::cout << "No Flash is VK_F5 \n";
	std::cout << "Chams is VK_F9 \n";
	std::cout << "Radar is VK_F10 \n";
	std::cout << "\n";

	while (true)
	{
		pMisc->Trigger();
		pVisuals->GlowESP();
		pVisuals->Chams();
		pMisc->Radar();
		pVisuals->noFlash();
	}
	delete m;
	return 0;
}

