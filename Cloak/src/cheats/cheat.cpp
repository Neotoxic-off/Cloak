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
    if (BuildHook(this->module, this->offset, this->bypass, this->target))
    {
        Log(LOG_SUCCESS, std::format("[{}+0x{:x}] {}", this->module->name, this->offset, LOG_SUCCESS_HOOKING_CHEAT).c_str());
        return true;
    }

    Log(LOG_ERROR, std::format("[{}+0x{:x}] {}", this->module->name, this->offset, LOG_ERROR_HOOKING_CHEAT).c_str());
    return false;
}

bool Cheat::UnHook()
{
    if (RemoveHook(this->module, this->offset))
    {
        Log(LOG_SUCCESS, std::format("[{}+0x{:x}] {}", this->module->name, this->offset, LOG_SUCCESS_UNHOOKING_CHEAT).c_str());
        return true;
    }

    Log(LOG_ERROR, std::format("[{}+0x{:x}] {}", this->module->name, this->offset, LOG_ERROR_UNHOOKING_CHEAT).c_str());
    return false;
}
