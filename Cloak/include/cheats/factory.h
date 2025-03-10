#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include <format>
#include <psapi.h>
#include <string>
#include <map>
#include <locale>
#include <codecvt>
#include <shlwapi.h>

#include "minhook.h"

#include "utils/logger.h"
#include "constants/logs.h"
#include "utils/hooks.h"

#include "cheats/cheat.h"

class Factory
{
    public:
        std::vector<Cheat> cheats;

        Factory();
        ~Factory();

        void Initialize();
        void HookCheats();
        void ReHookCheats();
        void UnHookCheats();
};
