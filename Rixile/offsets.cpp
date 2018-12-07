#include "offsets.h"

namespace offsets
{
	OFFSET  dwClientState;
	OFFSET  localPlayer;
	OFFSET  iHealth = 0x100;
	OFFSET  teamNum = 0xF4;
	OFFSET  entityList;
	OFFSET  crosshairID = 0xB390;
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
	OFFSET  maxPlayers = 0x310;
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
	OFFSET  m_szCustomName = 0x303C;
	OFFSET  bSpottedMask = 0x980;
	OFFSET  m_iViewModelIndex = 0x3210;
	OFFSET  m_nModelIndex = 0x254;
	OFFSET  m_hViewModel = 0x32DC;
	OFFSET  m_iEntityQuality = 0x2F9C;
	OFFSET  clientCMD;
	OFFSET  sendPackets;
}



