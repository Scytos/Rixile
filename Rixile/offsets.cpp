#include "Offsets.h"
#include "Includes.h"

namespace offsets
{
	OFFSET  dwClientState;
	OFFSET  localPlayer;
	OFFSET  teamNum = 0xF4;
	OFFSET  entityList;
	OFFSET  crosshairID = 0xB394;
	OFFSET  bDormant = 0xED;
	OFFSET  dwForceAttack;
	OFFSET  dwForceJump;
	OFFSET  flashAlpha = 0xA3DC;
	OFFSET  flashDuration = 0xA3E0;
	OFFSET  isScoped = 0x390A;
	OFFSET  vecVel = 0x114;
	OFFSET  dwGlow;
	OFFSET  dwGlowIdx = 0xA3F8;
	OFFSET  m_viewPunchAngle = 0x3020;
	OFFSET  m_iShotsFired = 0xA370;
	OFFSET  m_aimPunchAngle = 0x302C;
	OFFSET  m_vecViewOffset = 0x108;
	OFFSET  dwClientState_ViewAngles = 0x4D10;
	OFFSET  m_bSpotted = 0x93D;
	OFFSET  maxPlayers = 0x388;
	OFFSET  m_iFOVStart = 0x31E8;
	OFFSET  hActiveWeapon = 0x2EF8;
	OFFSET  m_iItemDefinitionIndex = 0x2FAA;
	OFFSET  setClantag;
	OFFSET  forceUpdate;
	OFFSET  enginePointer;
	OFFSET  m_hMyWeapons = 0x2DF8;
	OFFSET  m_iAccountID = 0x2FC8;
	OFFSET  m_OriginalOwnerXuidLow = 0x31B0;
	OFFSET  m_OriginalOwnerXuidHigh = 0x31B4;
	OFFSET  m_iItemIDLow = 0x2FB4;
	OFFSET  m_iItemIDHigh = 0x2FC0;
	OFFSET  m_nFallbackPaintKit = 0x31B8;
	OFFSET  m_nFallbackSeed = 0x31BC;
	OFFSET  m_flFallbackWear = 0x31C0;
	OFFSET  m_nFallbackStatTrak = 0x31C4;
	//OFFSET  m_szCustomName = 0x303C;
	std::string m_szCustomName = "painkit.m_szCustomName"; // is a string now found it after reversing
	OFFSET  bSpottedMask = 0x980;
	OFFSET  m_iViewModelIndex = 0x3210;
	OFFSET  m_nModelIndex = 0x254;
	OFFSET  m_hViewModel = 0x32DC;
	OFFSET  m_iEntityQuality = 0x2F9C;
	OFFSET  m_iHealth = 0x100;
	OFFSET  m_fFlags = 0x104;
	OFFSET  m_MoveType = 0x25C;
	OFFSET  clientCMD;
	OFFSET  sendPackets;
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


