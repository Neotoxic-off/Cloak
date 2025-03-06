#include "pch.h"

#include "cheats/cheat.h"
#include "cheats/factory.h"

Factory::Factory()
{
}

Factory::~Factory()
{
}

void Factory::Initialize()
{
    HookCheats();
}

void Factory::ReHookCheats()
{
    UnHookCheats();
    HookCheats();
}

void Factory::HookCheats()
{
    Log(LOG_WAIT, LOG_WAIT_HOOKING_CHEATS);

    uint16_t failed = 0;

    for (std::vector<Cheat>::iterator it = this->Cheats.begin(); it != this->Cheats.end(); ++it)
    {
        if (!it->Hook()) {
            failed++;
        }
    }

    if (failed > 0)
    {
        Log(LOG_ERROR, LOG_ERROR_HOOKING_CHEATS);
        return;
    }

    Log(LOG_SUCCESS, LOG_SUCCESS_HOOKING_CHEATS);
}

void Factory::UnHookCheats()
{
    Log(LOG_WAIT, LOG_WAIT_UNHOOKING_CHEATS);

    uint16_t failed = 0;

    for (std::vector<Cheat>::iterator it = this->Cheats.begin(); it != this->Cheats.end(); ++it)
    {
        if (!it->UnHook()) {
            failed++;
        }
    }

    if (failed > 0)
    {
        Log(LOG_ERROR, LOG_ERROR_UNHOOKING_CHEATS);
        return;
    }

    Log(LOG_SUCCESS, LOG_SUCCESS_UNHOOKING_CHEATS);
}
