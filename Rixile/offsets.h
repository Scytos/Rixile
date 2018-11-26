#pragma once
#include <Windows.h>

typedef unsigned long OFFSET;
namespace offsets
{
	extern OFFSET dwClientState;
	extern OFFSET localPlayer;
	extern OFFSET iHealth;
	extern OFFSET teamNum;
	extern OFFSET entityList;
	extern OFFSET crosshairID;
	extern OFFSET bDormant;
	extern OFFSET dwForceAttack;
	extern OFFSET dwForceJump;
	extern OFFSET flashAlpha;
	extern OFFSET flashDuration;
	extern OFFSET isScoped;
	extern OFFSET vecVel;
	extern OFFSET dwGlow;
	extern OFFSET dwGlowIdx;
	extern OFFSET m_viewPunchAngle;
	extern OFFSET m_iShotsFired;
	extern OFFSET m_aimPunchAngle;
	extern OFFSET m_vecViewOffset;
	extern OFFSET dwClientState_ViewAngles;
	extern OFFSET m_bSpotted;
	extern OFFSET maxPlayers;
	extern OFFSET m_iFOVStart;
	extern OFFSET m_hMyWeapons;
	extern OFFSET m_OriginalOwnerXuidLow;
	extern OFFSET m_OriginalOwnerXuidHigh;
	extern OFFSET m_iItemDefinitionIndex;
	extern OFFSET hActiveWeapon;
	extern OFFSET m_nFallbackPaintKit;
	extern OFFSET m_flFallbackWear;
	extern OFFSET m_iItemIDHigh;
	extern OFFSET m_iViewModelIndex;
	extern OFFSET m_nModelIndex;
	extern OFFSET m_hViewModel;
	extern OFFSET m_iEntityQuality;
}