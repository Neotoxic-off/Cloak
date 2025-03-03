#pragma once

#include "pch.h"

#include <iostream>
#include <stdio.h>
#include <format>
#include <windows.h>
#include <tlhelp32.h>

#include "minhook.h"
#include "logger.h"
#include "modules/debugger.h"
#include "modules/presence.h"

#include "game/cheat.h"
#include "utils/settings.h"
#include "utils/logs.h"

#if _WIN64 
#pragma comment(lib, "libMinHook.x64.lib")
#else
#pragma comment(lib, "libMinHook.x86.lib")
#endif

class Core
{
    private:
        Logger logger;

        Presence presence;
        Debugger debugger;
        Cheat cheat;

    public:
        Core();
        ~Core();

        void PatchPresence();
        void PatchDebugger();
        void WaitProcess();
        void Run();
};
