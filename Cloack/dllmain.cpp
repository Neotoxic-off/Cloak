#include "pch.h"
#include "core.h"

#include <windows.h>
#include <tlhelp32.h>

DWORD WINAPI Start(LPVOID lpParam)
{
	Core core = Core();

	core.ApplySecurityModules();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, Start, NULL, 0, NULL);
    }

    return TRUE;
}
