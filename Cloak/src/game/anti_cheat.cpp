#include "pch.h"
#include "game/anti_cheat.h"

AntiCheat::AntiCheat()
{
	this->Assemly = (uintptr_t)GetModuleHandle((LPCWSTR)"PhotonRealtime.dll");
}

void DullStart()
{
	std::cout << "Anti - Cheat start Bypassed" << std::endl;
}

void AntiCheat::NoStart()
{
	MH_CreateHook((LPVOID*)(this->Assemly + 0x3818830), &DullStart, NULL);
}

AntiCheat::~AntiCheat()
{
}
