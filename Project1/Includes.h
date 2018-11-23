#pragma once
#include "MemManager.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include "offsets.h"
#include <chrono>
#include <thread>


extern MemManager *m;
extern void SaveCPU(int ms);
extern void PrintOffsetsConsole(const char* text, DWORD Offset);