#pragma once

#include <windows.h>
#include <iostream>
#include "MinHook.h"
#include "logger.h"
#include "hooks.h"

class Cheat
{
    private:
        uintptr_t Assemly;

    public:
        Cheat();
        ~Cheat();

        void ForceUsername();
        void ForceHost();
        void ForceBasementNoKeys();
        void ForceBasementUnlocked();
        void UnlockAllDoors();
        void ForceNeverDead();
};
