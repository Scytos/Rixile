#pragma once
#include "MemManager.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include "Offsets.h"
#include <chrono>
#include <thread>
#include "LocalPlayer.h"
#include "Entity.h"
#include <map>

extern MemManager *m;
extern void SaveCPU(int ms);
extern void PrintOffsetsConsole(const char* text, DWORD Offset);
extern void PrintConsole(const char* text);