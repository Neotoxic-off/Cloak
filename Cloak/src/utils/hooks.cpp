#include "pch.h"

#include "utils/hooks.h"

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

bool ValidateOffset(HMODULE module, int offset)
{
    uintptr_t targetAddress = (uintptr_t)module + offset;

    if (!IsValidMemory(targetAddress))
    {
        return false;
    }

    return true;
}

bool BuildHook(Module* module, int offset, LPVOID bypass, LPVOID* target)
{
    bool offset_status = false;
    MH_STATUS create_status = MH_UNKNOWN;
    MH_STATUS enable_status = MH_UNKNOWN;

    if (ValidateOffset(module->handle, offset) == true)
    {
        create_status = MH_CreateHook((LPVOID)(module + offset), bypass, target);
        if (create_status != MH_OK) {
            Log(LOG_ERROR, std::format("[{}+0x{:x}] {}", module->name, offset, LOG_ERROR_HOOK_CREATE_FAILED).c_str());
            return false;
        }

        enable_status = MH_EnableHook((LPVOID)(module + offset));
        if (enable_status != MH_OK) {
            Log(LOG_ERROR, std::format("[{}+0x{:x}] {}", module->name, offset, LOG_ERROR_HOOK_ENABLE_FAILED).c_str());
            return false;
        }

        return true;
    }

    Log(LOG_ERROR, std::format("[{}+0x{:x}] {}", module->name, offset, LOG_ERROR_OFFSET_NOT_READY).c_str());

    return false;
}

bool RemoveHook(Module* module, int offset)
{
    bool offset_status = false;
    MH_STATUS remove_status = MH_UNKNOWN;
    MH_STATUS disable_status = MH_UNKNOWN;

    if (ValidateOffset(module->handle, offset) == true)
    {
        remove_status = MH_RemoveHook((LPVOID)(module + offset));
        if (remove_status != MH_OK) {
            Log(LOG_ERROR, std::format("[{}+0x{:x}] {}", module->name, offset, LOG_ERROR_HOOK_REMOVING_FAILED).c_str());
            return false;
        }

        disable_status = MH_DisableHook((LPVOID)(module + offset));
        if (disable_status != MH_OK) {
            Log(LOG_ERROR, std::format("[{}+0x{:x}] {}", module->name, offset, LOG_ERROR_HOOK_DISABLING_FAILED).c_str());
            return false;
        }
        return true;
    }

    Log(LOG_ERROR, std::format("[{}+0x{:x}] {}", module->name, offset, LOG_ERROR_OFFSET_NOT_READY).c_str());

    return false;
}
