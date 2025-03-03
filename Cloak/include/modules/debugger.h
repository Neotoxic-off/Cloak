#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <winternl.h>

#include "logger.h"
#include "utils/logs.h"

typedef NTSTATUS(NTAPI* pNtSetInformationProcess)
(
    HANDLE ProcessHandle,
    UINT ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength
);

#define ProcessDebugFlags 0x1F
#define ProcessDebugObjectHandle 0x1E

class Debugger
{
    private:
        void ClearPebFlags(PVOID);
        pNtSetInformationProcess GetNtSetInformationProcess();
        void DisableDebuggerDetection();

    public:
        Debugger();
        ~Debugger();

        void Patch();
};
