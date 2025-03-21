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

#include "modules/protection.h"
#include "modules/presence.h"

#include "user/sample.h"

#include "utils/logger.h"
#include "constants/settings.h"

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

        Sample sample;

    public:
        Core();
        ~Core();

        void PatchPresence();
        void ApplyProtection();
        void WaitProcess();
        void Run();
        void UnLoad();
};
