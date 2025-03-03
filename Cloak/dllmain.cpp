#include "pch.h"
#include "core.h"

#include <windows.h>
#include <tlhelp32.h>

DWORD WINAPI Start(LPVOID lpParam)
{
    Core core = Core();

    core.PatchDebugger();
    core.PatchPresence();
    core.WaitProcess();
    core.Run();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    HANDLE hThread = NULL;

    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Start, hModule, 0, nullptr);
            break;

        case DLL_PROCESS_DETACH:
            if (hThread)
            {
                FreeLibraryAndExitThread(hModule, 0);
                CloseHandle(hThread);
                hThread = NULL;
            }
            break;
    }

    return TRUE;
}
