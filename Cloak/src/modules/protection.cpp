#include "pch.h"
#include "modules/protection.h"
#include <windows.h>
#include <tlhelp32.h>
#include <intrin.h>
#include <cstring>

Protection::Protection()
{
}

Protection::~Protection()
{
}

void Protection::ClearPebFlags(PVOID pebAddress)
{
    Log(LOG_INFO, LOG_WAIT_DEBUGGER_CLEARING);

    BYTE* peb = static_cast<BYTE*>(pebAddress);
    DWORD* ntGlobalFlag = reinterpret_cast<DWORD*>(peb + 0xBC);

    peb[2] = 0;
    *ntGlobalFlag &= ~0x70;

    Log(LOG_SUCCESS, LOG_SUCCESS_DEBUGGER_CLEARED);
}

pNtSetInformationProcess Protection::GetNtSetInformationProcess()
{
    Log(LOG_WAIT, LOG_WAIT_NTSET_CLEARING);

    HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
    if (!hNtdll)
    {
        Log(LOG_ERROR, LOG_ERROR_NTDLL_HANDLE_FAILED);
        return nullptr;
    }

    pNtSetInformationProcess NtSetInfoProc = (pNtSetInformationProcess)GetProcAddress(hNtdll, "NtSetInformationProcess");
    if (!NtSetInfoProc)
    {
        return nullptr;
    }

    return NtSetInfoProc;
}

void Protection::DisableDebuggerDetection()
{
    DWORD oldProtect;

    typedef BOOL(WINAPI* pIsDebuggerPresent)();
    pIsDebuggerPresent IsDebuggerPresent = (pIsDebuggerPresent)GetProcAddress(GetModuleHandleA("kernel32.dll"), "IsDebuggerPresent");

    if (IsDebuggerPresent)
    {
        VirtualProtect(IsDebuggerPresent, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
        *(BYTE*)IsDebuggerPresent = 0xC3;
        VirtualProtect(IsDebuggerPresent, 1, oldProtect, &oldProtect);
        Log(LOG_SUCCESS, LOG_SUCCESS_DEBUGGER_DISABLED);

        return;
    }

    Log(LOG_ERROR, LOG_ERROR_NTSET_INFO_RETRIEVE_FAILED);
}

void Protection::Apply()
{
    Log(LOG_WAIT, LOG_WAIT_PATCHING);

    PVOID pebAddress = (PVOID)__readgsqword(0x60);

    if (pebAddress)
    {
        ClearPebFlags(pebAddress);
        DisableDebuggerDetection();
        BypassBreakpoints();
        BypassTimingChecks();
        NeutralizeExceptionHandlers();
        Log(LOG_SUCCESS, LOG_SUCCESS_PATCHED);

        return;
    }
}

void Protection::BypassBreakpoints()
{
    CONTEXT ctx = {};
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    HANDLE hThread = GetCurrentThread();

    if (GetThreadContext(hThread, &ctx))
    {
        ctx.Dr0 = ctx.Dr1 = ctx.Dr2 = ctx.Dr3 = ctx.Dr6 = ctx.Dr7 = 0;
        SetThreadContext(hThread, &ctx);
        Log(LOG_SUCCESS, LOG_SUCCESS_PRESENCE_PATCHED);
        return;
    }

    Log(LOG_ERROR, LOG_ERROR_HOOK_ENABLE_FAILED);
}

void Protection::BypassTimingChecks()
{
    BYTE patch[] = { 0x31, 0xC0, 0xC3 };
    DWORD oldProtect;
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    FARPROC GetTickCountAddr = GetProcAddress(hKernel32, "GetTickCount");

    if (GetTickCountAddr)
    {
        VirtualProtect(GetTickCountAddr, sizeof(patch), PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy(GetTickCountAddr, patch, sizeof(patch));
        VirtualProtect(GetTickCountAddr, sizeof(patch), oldProtect, &oldProtect);
    }
}

void Protection::NeutralizeExceptionHandlers()
{
    SetUnhandledExceptionFilter(NULL);
}
