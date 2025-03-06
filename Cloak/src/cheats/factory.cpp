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

    for (std::vector<Cheat>::iterator it = this->Cheats.begin(); it != this->Cheats.end(); ++it)
    {
        it->Hook();
    }

    Log(LOG_SUCCESS, LOG_SUCCESS_HOOKING_CHEATS);
}

void Factory::UnHookCheats()
{
    Log(LOG_WAIT, LOG_WAIT_UNHOOKING_CHEATS);

    for (std::vector<Cheat>::iterator it = this->Cheats.begin(); it != this->Cheats.end(); ++it)
    {
        it->UnHook();
    }

    Log(LOG_SUCCESS, LOG_SUCCESS_UNHOOKING_CHEATS);
}
