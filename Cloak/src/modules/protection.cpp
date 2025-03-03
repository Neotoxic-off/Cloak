#include "pch.h"
#include "modules/protection.h"
#include <windows.h>
#include <tlhelp32.h>
#include <intrin.h>
#include <cstring>

Protection::Protection() {}
Protection::~Protection() {}

void Protection::ClearPebFlags(PVOID pebAddress)
{
    Log(LOG_INFO, LOG_WAIT_DEBUGGER_CLEARING);

    BYTE* peb = static_cast<BYTE*>(pebAddress);
    DWORD* ntGlobalFlag = reinterpret_cast<DWORD*>(peb + 0xBC);

    peb[2] = 0;
    *ntGlobalFlag &= ~0x70;

    Log(LOG_SUCCESS, LOG_SUCCESS_DEBUGGER_CLEARED);
}

DWORD(WINAPI* Protection::TrueGetModuleFileName)(HMODULE hModule, LPSTR lpFilename, DWORD nSize) = GetModuleFileNameA;

DWORD WINAPI Protection::HookedGetModuleFileName(HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
    DWORD result = TrueGetModuleFileName(hModule, lpFilename, nSize);
    if (result != 0) {
        // Modify the module name
        std::string newName = "newname.dll";
        strncpy_s(lpFilename, nSize, newName.c_str(), newName.length());
    }
    return result;
}

void Protection::RenameModule()
{
    Log(LOG_INFO, "Renaming module");

    MH_CreateHook(&GetModuleFileNameA, &HookedGetModuleFileName, reinterpret_cast<void**>(&TrueGetModuleFileName));
    MH_EnableHook(&GetModuleFileNameA);

    Log(LOG_SUCCESS, "Renamed module");
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
        Log(LOG_ERROR, LOG_ERROR_NTSET_RETRIEVE_FAILED);
        return nullptr;
    }

    Log(LOG_SUCCESS, LOG_SUCCESS_NTSET_RETRIEVED);
    return NtSetInfoProc;
}

void Protection::DisableDebuggerDetection()
{
    Log(LOG_INFO, LOG_INFO_DISABLE_DEBUGGER);

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
        RenameModule();
        ClearPebFlags(pebAddress);
        DisableDebuggerDetection();
        BypassBreakpoints();
        AllowMemoryAccess();
        BypassAntiDebuggingTechniques();
        BypassTimingChecks();
        NeutralizeExceptionHandlers();
        UnhookDebugAPIs();
        Log(LOG_SUCCESS, LOG_SUCCESS_PATCHED);

        return;
    }

    Log(LOG_ERROR, LOG_ERROR_PEB_RETRIEVE_FAILED);
}

void Protection::BypassBreakpoints()
{
    Log(LOG_INFO, LOG_INFO_BYPASSING_BREAKPOINTS);

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

void Protection::AllowMemoryAccess()
{
    Log(LOG_INFO, LOG_INFO_ALLOWING_MEMORY_ACCESS);

    HMODULE hNtdll = GetModuleHandleA(NTDLL);
    DWORD oldProtect = NULL;
    FARPROC NtQueryVirtualMemory = NULL;
    FARPROC NtQuerySystemInformation = NULL;

    if (!hNtdll)
    {
        Log(LOG_ERROR, LOG_ERROR_NTDLL_HANDLE_FAILED);
        return;
    }

    NtQueryVirtualMemory = GetProcAddress(hNtdll, "NtQueryVirtualMemory");

    if (NtQueryVirtualMemory)
    {
        BYTE patch[] = { 0x31, 0xC0, 0xC3 }; // xor eax, eax; ret
        oldProtect = NULL;

        if (VirtualProtect(NtQueryVirtualMemory, sizeof(patch), PAGE_EXECUTE_READWRITE, &oldProtect))
        {
            memcpy(NtQueryVirtualMemory, patch, sizeof(patch));
            VirtualProtect(NtQueryVirtualMemory, sizeof(patch), oldProtect, &oldProtect);
            Log(LOG_SUCCESS, LOG_SUCCESS_MEMORY_QUERY_BYPASSED);
        }
        else
        {
            Log(LOG_ERROR, LOG_ERROR_MEMORY_PROTECTION_FAILED);
        }
    }
    else
    {
        Log(LOG_ERROR, LOG_ERROR_NTQUERYVIRTUALMEMORY_FAILED);
    }

    NtQuerySystemInformation = GetProcAddress(hNtdll, "NtQuerySystemInformation");

    if (NtQuerySystemInformation)
    {
        BYTE patch[] = { 0x33, 0xC0, 0xC2, 0x10, 0x00 }; // xor eax, eax; ret 10h
        oldProtect = NULL;

        if (VirtualProtect(NtQuerySystemInformation, sizeof(patch), PAGE_EXECUTE_READWRITE, &oldProtect))
        {
            memcpy(NtQuerySystemInformation, patch, sizeof(patch));
            VirtualProtect(NtQuerySystemInformation, sizeof(patch), oldProtect, &oldProtect);
            Log(LOG_SUCCESS, LOG_SUCCESS_SYSTEM_QUERY_BYPASSED);

            return;
        }

        Log(LOG_ERROR, LOG_ERROR_SYSTEM_QUERY_PATCH_FAILED);
        return;
    }

    Log(LOG_ERROR, LOG_ERROR_NTQUERYSYSTEMINFORMATION_FAILED);
    return;
}


void Protection::BypassAntiDebuggingTechniques()
{
    Log(LOG_INFO, LOG_INFO_BYPASSING_ANTI_DEBUG);
}

void Protection::BypassTimingChecks()
{
    Log(LOG_INFO, LOG_INFO_NEUTRALIZING_TIMING_CHECKS);
    BYTE patch[] = { 0x31, 0xC0, 0xC3 };
    DWORD oldProtect;
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    FARPROC GetTickCountAddr = GetProcAddress(hKernel32, "GetTickCount");

    if (GetTickCountAddr)
    {
        VirtualProtect(GetTickCountAddr, sizeof(patch), PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy(GetTickCountAddr, patch, sizeof(patch));
        VirtualProtect(GetTickCountAddr, sizeof(patch), oldProtect, &oldProtect);

        Log(LOG_SUCCESS, LOG_SUCCESS_PROCESS_LOADING);
    }
}

void Protection::NeutralizeExceptionHandlers()
{
    Log(LOG_INFO, LOG_INFO_NEUTRALIZING_EXCEPTIONS);

    SetUnhandledExceptionFilter(NULL);
}

void Protection::UnhookDebugAPIs()
{
    Log(LOG_INFO, LOG_INFO_RESTORING_HOOKS);
}
