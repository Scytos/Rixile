#include "Includes.h"

MemManager *m = new MemManager();

void SaveCPU(int ms)
{
	return std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}