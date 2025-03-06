#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <winternl.h>
#include <intrin.h>

#include "utils/logger.h"
#include "utils/logs.h"
#include "utils/hooks.h"

#define NTDLL "ntdll.dll"

typedef NTSTATUS(NTAPI* pNtSetInformationProcess)
(
    HANDLE ProcessHandle,
    UINT ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength
    );

typedef NTSTATUS(NTAPI* pNtDelayExecution)(BOOL Alertable, PLARGE_INTEGER DelayInterval);

#define ProcessDebugFlags 0x1F
#define ProcessDebugObjectHandle 0x1E

class Protection
{
    private:
        void ClearPebFlags(PVOID);
        pNtSetInformationProcess GetNtSetInformationProcess();
        void DisableDebuggerDetection();
        void BypassBreakpoints();
        void BypassTimingChecks();
        void NeutralizeExceptionHandlers();

    public:
        Protection();
        ~Protection();

        void Apply();
};
