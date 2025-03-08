#pragma once

#include <windows.h>
#include <format>

#include "game/base.h"

#include "cheats/factory.h"

#include "constants/offsets.h"
#include "constants/modules.h"

class Sample
{
    private:
        Factory factory;

    public:
        Sample();
        ~Sample();

        void Run();
        void ReHookCheats();
        void HookCheats();
        void UnHookCheats();
};
