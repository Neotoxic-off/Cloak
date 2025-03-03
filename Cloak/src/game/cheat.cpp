#include "pch.h"
#include "game/cheat.h"

Cheat::Cheat()
{
    this->Assemly = (uintptr_t)GetModuleHandle(MODULE_NAME);
}

Cheat::~Cheat()
{
}
