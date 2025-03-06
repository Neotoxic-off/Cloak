#include "pch.h"

#include "cheats/cheat.h"

Cheat::Cheat(Module* module, int offset, LPVOID bypass, LPVOID* target)
{
    this->ready = false;
    this->module = module;
    this->offset = offset;
    this->bypass = bypass;
    this->target = target;
}

Cheat::~Cheat()
{

}

bool Cheat::Hook()
{
    Log(LOG_WAIT, LOG_WAIT_HOOKING_CHEAT);

    if (BuildHook(this->module, this->offset, this->bypass, this->target))
    {
        Log(LOG_SUCCESS, LOG_SUCCESS_HOOKING_CHEAT);
        return true;
    }

    Log(LOG_ERROR, LOG_ERROR_HOOKING_CHEAT);
    return false;
}

bool Cheat::UnHook()
{
    Log(LOG_WAIT, LOG_WAIT_UNHOOKING_CHEAT);

    if (RemoveHook(this->module, this->offset))
    {
        Log(LOG_SUCCESS, LOG_SUCCESS_UNHOOKING_CHEAT);
        return true;
    }

    Log(LOG_ERROR, LOG_ERROR_UNHOOKING_CHEAT);
    return false;
}
