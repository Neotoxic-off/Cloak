#include "pch.h"

#include "game/cheat.h"

Cheat::Cheat()
{
    this->Assemly = (uintptr_t)GetModuleHandle(MODULE_NAME);
}

Cheat::~Cheat()
{
}

void Cheat::Run()
{
    Log(LOG_WAIT, "Executing cheat modules");

    Example();
}

void Cheat::Example()
{
    bool hook_build_status = BuildHook(this->Assemly, OFFSET_EXAMPLE, &ForceTrue, nullptr);

    if (hook_build_status)
    {
        Log(LOG_SUCCESS, "Example");
    }
    else
    {
        Log(LOG_INFO, "Skipped Example");
    }
}
