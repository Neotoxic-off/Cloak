#include "pch.h"

#include "modules/debugger.h"

Debugger::Debugger()
{
}

Debugger::~Debugger()
{
}

void Debugger::ClearPebFlags(PVOID pebAddress)
{
    Log(LOG_INFO, "Clearing PEB debugger flags");

    BYTE* peb = static_cast<BYTE*>(pebAddress);
    DWORD* ntGlobalFlag = NULL;

    peb[2] = 0;

    ntGlobalFlag = reinterpret_cast<DWORD*>(peb + 0xBC);
    *ntGlobalFlag &= ~0x70;

    Log(LOG_SUCCESS, "PEB debugger flags cleared");
}

pNtSetInformationProcess Debugger::GetNtSetInformationProcess()
{
    Log(LOG_INFO, "Retrieving NtSetInformationProcess function address");

    HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
    pNtSetInformationProcess NtSetInformationProcess = NULL;

    if (!hNtdll)
    {
        Log(LOG_ERROR, "Failed to get ntdll.dll module handle");
        return nullptr;
    }

    NtSetInformationProcess = (pNtSetInformationProcess)GetProcAddress(
        hNtdll,
        "NtSetInformationProcess"
    );

    if (!NtSetInformationProcess)
    {
        Log(LOG_ERROR, "Failed to get NtSetInformationProcess function address");
    }
    else
    {
        Log(LOG_SUCCESS, "NtSetInformationProcess function address retrieved");
    }

    return NtSetInformationProcess;
}

void Debugger::DisableDebuggerDetection()
{
    Log(LOG_INFO, "Disabling debugger detection");

    HANDLE hProcess = GetCurrentProcess();
    DWORD isDebuggerPresent = 0;
    HANDLE hNull = NULL;
    pNtSetInformationProcess NtSetInformationProcess = GetNtSetInformationProcess();

    if (!NtSetInformationProcess)
    {
        Log(LOG_ERROR, "Failed to retrieve NtSetInformationProcess, skipping debugger disabling");
        return;
    }

    NtSetInformationProcess(hProcess, ProcessDebugFlags, &isDebuggerPresent, sizeof(DWORD));
    NtSetInformationProcess(hProcess, ProcessDebugObjectHandle, &hNull, sizeof(HANDLE));

    Log(LOG_SUCCESS, "Debugger detection disabled");
}

void Debugger::Patch()
{
    Log(LOG_WAIT, "Patching debugger detection");

    PVOID pebAddress = (PVOID)__readgsqword(0x60);

    if (pebAddress)
    {
        ClearPebFlags(pebAddress);
        DisableDebuggerDetection();
        Log(LOG_SUCCESS, "Patched debugger detection");
    }
    else
    {
        Log(LOG_ERROR, "Failed to retrieve PEB address");
    }
}
