#include "pch.h"

#include "modules/presence.h"

Presence::Presence()
{
}

Presence::~Presence()
{
}

void Presence::Patch()
{
    Log(LOG_WAIT, LOG_WAIT_PRESENCE_PATCHING);

    DWORD pid = GetCurrentProcessId();
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe)) {
        do {
            if (pe.th32ProcessID == pid) {
                memset(pe.szExeFile, 0, sizeof(pe.szExeFile));
            }
        } while (Process32Next(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);

    Log(LOG_SUCCESS, LOG_SUCCESS_PRESENCE_PATCHED);
}
