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
    Log(LOG_INFO, LOG_WAIT_DEBUGGER_CLEARING);

    BYTE* peb = static_cast<BYTE*>(pebAddress);
    DWORD* ntGlobalFlag = NULL;

    peb[2] = 0;

    ntGlobalFlag = reinterpret_cast<DWORD*>(peb + 0xBC);
    *ntGlobalFlag &= ~0x70;

    Log(LOG_SUCCESS, LOG_SUCCESS_DEBUGGER_CLEARED);
}

pNtSetInformationProcess Debugger::GetNtSetInformationProcess()
{
    Log(LOG_INFO, LOG_WAIT_NTSET_CLEARING);

    HMODULE hNtdll = GetModuleHandleA(NTDLL);
    pNtSetInformationProcess NtSetInformationProcess = NULL;

    if (!hNtdll)
    {
        Log(LOG_ERROR, LOG_ERROR_NTDLL_HANDLE_FAILED);
        return nullptr;
    }

    NtSetInformationProcess = (pNtSetInformationProcess)GetProcAddress(
        hNtdll,
        "NtSetInformationProcess"
    );

    if (!NtSetInformationProcess)
    {
        Log(LOG_ERROR, LOG_ERROR_NTSET_RETRIEVE_FAILED);
    }
    else
    {
        Log(LOG_SUCCESS, LOG_SUCCESS_NTSET_RETRIEVED);
    }

    return NtSetInformationProcess;
}

void Debugger::DisableDebuggerDetection()
{
    Log(LOG_INFO, LOG_INFO_DISABLE_DEBUGGER);

    HANDLE hProcess = GetCurrentProcess();
    DWORD isDebuggerPresent = 0;
    HANDLE hNull = NULL;
    pNtSetInformationProcess NtSetInformationProcess = GetNtSetInformationProcess();

    if (!NtSetInformationProcess)
    {
        Log(LOG_ERROR, LOG_ERROR_NTSET_INFO_RETRIEVE_FAILED);
        return;
    }

    NtSetInformationProcess(hProcess, ProcessDebugFlags, &isDebuggerPresent, sizeof(DWORD));
    NtSetInformationProcess(hProcess, ProcessDebugObjectHandle, &hNull, sizeof(HANDLE));

    Log(LOG_SUCCESS, LOG_SUCCESS_DEBUGGER_DISABLED);
}

void Debugger::Patch()
{
    Log(LOG_WAIT, LOG_WAIT_PATCHING);

    PVOID pebAddress = (PVOID)__readgsqword(0x60);

    if (pebAddress)
    {
        ClearPebFlags(pebAddress);
        DisableDebuggerDetection();
        Log(LOG_SUCCESS, LOG_SUCCESS_PATCHED);
    }
    else
    {
        Log(LOG_ERROR, LOG_ERROR_PEB_RETRIEVE_FAILED);
    }
}
