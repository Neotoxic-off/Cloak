#include "pch.h"
#include "game/anti_cheat.h"

AntiCheat::AntiCheat()
{
	this->Assemly = (uintptr_t)GetModuleHandle(L"GameAssembly.dll");
}

void DullStart()
{
	Log(LOG_SUCCESS, "Anti - Cheat start bypassed");
}

void AntiCheat::NoStart()
{
	MH_STATUS status = MH_CreateHook((LPVOID*)(this->Assemly + 0x3818830), &DullStart, NULL);
    if (status != MH_OK) {
        Log(LOG_ERROR, "Failed to create hook!");
        return;
    }

    if (MH_EnableHook((LPVOID)(this->Assemly + 0x3818830)) != MH_OK) {
        Log(LOG_ERROR, "Failed to enable hook!");
        return;
    }
}

AntiCheat::~AntiCheat()
{
}
