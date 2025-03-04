#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include <psapi.h>
#include <string>
#include <locale>
#include <codecvt>

#include "minhook.h"
#include "logger.h"
#include "hooks.h"

#include "utils/settings.h"

#include "game/base.h"
#include "game/offsets.h"

struct Module
{
    uintptr_t assembly;
    int offset;
    LPVOID bypass;
    LPVOID* target;
};

class Cheat
{
    private:
        uintptr_t Assemly;
        bool AssemblyLoaded;
        std::vector<Module> Catalog;

        void LoadAssembly();

        void LoadCatalog();
        void BuildCatalog();
        void ExecuteCatalog(uintptr_t assembly, int offset, LPVOID bypass, LPVOID* target);
        std::string GetModuleName(uintptr_t handle);

    public:
        Cheat();
        ~Cheat();

        void Run();
};
