#pragma once

#include <windows.h>
#include <format>

#include "game/base.h"
#include "game/pattern.h"

#include "cheats/factory.h"

#include "constants/offsets.h"
#include "constants/patterns.h"
#include "constants/modules.h"

class Sample
{
    private:
        Factory factory;
        Pattern pattern;

    public:
        Sample();
        ~Sample();

        void Run();
        void ReHookCheats();
        void HookCheats();
        void UnHookCheats();
        void ScanPatterns();
};
