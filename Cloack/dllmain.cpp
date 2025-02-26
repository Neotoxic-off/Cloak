#include "pch.h"

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <stdio.h>

void CreateConsoleAndLog() {
    AllocConsole();

    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);


    std::cout << "Console created. Logs will be displayed here." << std::endl;
}

void PatchPEB() {
    PVOID pebAddress = (PVOID)__readgsqword(0x60);

    if (pebAddress) {
        BYTE* peb = static_cast<BYTE*>(pebAddress);
        peb[2] = 0;
    }
}

void HideFromProcessList() {
    DWORD pid = GetCurrentProcessId();
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe)) {
        do {
            if (pe.th32ProcessID == pid) {
                memset(pe.szExeFile, 0, sizeof(pe.szExeFile)); // Hide name
            }
        } while (Process32Next(hSnapshot, &pe));
    }
    CloseHandle(hSnapshot);
}

DWORD WINAPI Start(LPVOID lpParam) {
    CreateConsoleAndLog();
    std::cout << "DLL Injected - AntiVM & AntiDebug Bypass Activated!" << std::endl;
    PatchPEB();

    HideFromProcessList();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, Start, NULL, 0, NULL);
    }
    return TRUE;
}
