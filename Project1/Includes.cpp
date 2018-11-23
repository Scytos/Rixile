#include "Includes.h"

MemManager *m = new MemManager();

void SaveCPU(int ms)
{
	return std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void PrintOffsetsConsole(const char* text, DWORD Offset) // Usage is simply is consists of a constchar and a dword
{
	std::cout << text << std::hex << Offset << std::endl;
}