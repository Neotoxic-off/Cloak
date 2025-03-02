#include "pch.h"

#include "hooks.h"

void BuildHook(uintptr_t assembly, int offset, LPVOID bypass, LPVOID* target)
{
    MH_STATUS create_status = MH_CreateHook((LPVOID)(assembly + offset), bypass, target);
    MH_STATUS enable_status = MH_UNKNOWN;
    std::string offsetStr = std::format("{:X}", offset);

    if (create_status != MH_OK) {
        Log(LOG_ERROR, std::format("(0x{}) Failed to create hook", offsetStr).c_str());
        return;
    }
    enable_status = MH_EnableHook((LPVOID)(assembly + offset));
    if (enable_status != MH_OK) {
        Log(LOG_ERROR, std::format("(0x{}) Failed to enable hook", offsetStr).c_str());
        return;
    }
}
