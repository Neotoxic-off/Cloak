#pragma once

#include <Windows.h>

#include "utils/logs.h"
#include "utils/logger.h"
#include "utils/modules.h"
#include "utils/hooks.h"

class Cheat
{
    private:
        Module* module;
        int offset;
        LPVOID bypass;
        LPVOID* target;
        bool ready;

    public:
        Cheat(Module*, int, LPVOID, LPVOID*);
        ~Cheat();

        void Hook();
        void UnHook();
};
