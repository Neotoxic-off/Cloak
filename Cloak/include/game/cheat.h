#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include <psapi.h>
#include <string>
#include <map>
#include <locale>
#include <codecvt>

#include "minhook.h"
#include "logger.h"
#include "hooks.h"

#include "utils/settings.h"

#include "game/base.h"
#include "game/offsets.h"

static const char* MODULE_GAME_ASSEMBLY = "GameAssembly.dll";
static const LPCWSTR LP_MODULE_GAME_ASSEMBLY = L"GameAssembly.dll";

struct CheatModule
{
    const char* moduleName;
    int offset;
    LPVOID bypass;
    LPVOID* target;
};

struct Module
{
    uintptr_t handle;
    LPCWSTR lpName;
    bool loaded;
};

class Cheat
{
    private:
        std::map<const char*, Module> Modules = {
            { MODULE_GAME_ASSEMBLY, { NULL, LP_MODULE_GAME_ASSEMBLY, false }}
        };
        std::vector<CheatModule> CheatModules = {
            { MODULE_GAME_ASSEMBLY, OFFSET_EXAMPLE, DummyTrue, nullptr }
        };

        void LoadModules();
        void BuildCheatModules();
        Module GetModule(const char* moduleName);
        void ExecuteCheatModule(const char* moduleName, int offset, LPVOID bypass, LPVOID* target);

    public:
        Cheat();
        ~Cheat();

        void Run();
        void ReloadCheatModules();
};
