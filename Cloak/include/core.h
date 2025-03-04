#pragma once

#include "pch.h"

#include <iostream>
#include <stdio.h>
#include <format>
#include <functional>
#include <map>
#include <windows.h>
#include <tlhelp32.h>

#include "minhook.h"
#include "logger.h"
#include "modules/protection.h"
#include "modules/presence.h"

#include "game/cheat.h"
#include "utils/settings.h"

#if _WIN64 
    #pragma comment(lib, "libMinHook.x64.lib")
#else
    #pragma comment(lib, "libMinHook.x86.lib")
#endif

class Core
{
    private:
        bool running;

        Logger logger;

        Presence presence;
        Protection protection;
        Cheat cheat;

    public:
        Core();
        ~Core();

        void PatchPresence();
        void ApplyProtection();
        void WaitProcess();
        void Run();
};
