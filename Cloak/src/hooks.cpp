#include "pch.h"

#include "hooks.h"

bool IsValidMemory(uintptr_t address)
{
    bool isCommitted = false;
    bool isExecutable = false;
    MEMORY_BASIC_INFORMATION mbi;

    if (VirtualQuery((LPCVOID)address, &mbi, sizeof(mbi)) == 0)
    {
        return false;
    }

    isCommitted = (mbi.State == MEM_COMMIT);
    isExecutable = (mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY));

    return isCommitted && isExecutable;
}

bool ValidateOffset(uintptr_t assembly, int offset)
{
    uintptr_t targetAddress = assembly + offset;

    if (!IsValidMemory(targetAddress))
    {
        Log(LOG_ERROR, "Offset is not ready or invalid");

        return false;
    }

    Log(LOG_SUCCESS, "Offset is ready");

    return true;
}

bool BuildHook(uintptr_t assembly, int offset, LPVOID bypass, LPVOID* target)
{
    bool offset_status = false;
    MH_STATUS create_status = MH_UNKNOWN;
    MH_STATUS enable_status = MH_UNKNOWN;
    std::string offsetStr = std::format("{:X}", offset);

    if (ValidateOffset(assembly, offset) == true)
    {
        create_status = MH_CreateHook((LPVOID)(assembly + offset), bypass, target);
        if (create_status != MH_OK) {
            Log(LOG_ERROR, std::format("(0x{}) Failed to create hook", offsetStr).c_str());
            return false;
        }

        enable_status = MH_EnableHook((LPVOID)(assembly + offset));
        if (enable_status != MH_OK) {
            Log(LOG_ERROR, std::format("(0x{}) Failed to enable hook", offsetStr).c_str());
            return false;
        }

        return true;
    }

    return false;
}
