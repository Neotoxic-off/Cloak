#include "pch.h"
#include "game/anti_cheat.h"

AntiCheat::AntiCheat()
{
	this->Assemly = (uintptr_t)GetModuleHandle((LPCWSTR)"PhotonRealtime.dll");
}

void DullStart()
{
	std::cout << "[Anti-Cheat] start bypassed" << std::endl;
}

void NullDetection()
{
	std::cout << "[Anti-Cheat] detection bypassed" << std::endl;
	return;
}

void AntiCheat::NoStart()
{
	MH_CreateHook((LPVOID*)(this->Assemly + 0x3817030), &DullStart, NULL);
}

void AntiCheat::NoDetection()
{
	MH_CreateHook((LPVOID*)(this->Assemly + 0x3817140), &NullDetection, NULL);
}

AntiCheat::~AntiCheat()
{
}
