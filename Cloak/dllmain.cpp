#include "pch.h"
#include "core.h"

#include <windows.h>
#include <tlhelp32.h>

DWORD WINAPI Start(LPVOID lpParam)
{
    Core core = Core();

    core.ApplySecurityModules();
    core.BypassAntiCheat();
    core.ForceUsername();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	HANDLE hThread = NULL;

    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Start, hModule, 0, nullptr);
    }

    return TRUE;
}
