#include "pch.h"
#include "game/cheat.h"

int __stdcall ForceZero()
{
    Log(LOG_SUCCESS, "Forced zero");

    return 0;
}

bool __stdcall ForceTrue()
{
    Log(LOG_INFO, "Forced true");
    return true;
}

bool __stdcall ForceFalse()
{
    Log(LOG_INFO, "Forced false");

    return false;
}

Cheat::Cheat()
{
    this->Assemly = (uintptr_t)GetModuleHandle(MODULE_NAME);
}

void Cheat::Force()
{
    Log(LOG_WAIT, "Forcing");

    bool hook_build_status = BuildHook(this->Assemly, OFFSET_FORCE, &ForceTrue, nullptr);

    if (hook_build_status == true)
    {
        Log(LOG_SUCCESS, "Forced");
    }
    else
    {
        Log(LOG_INFO, "Skipped force");
    }
}

Cheat::~Cheat()
{
}
