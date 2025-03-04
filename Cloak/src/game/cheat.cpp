#include "pch.h"

#include "game/cheat.h"

Cheat::Cheat()
{
}

Cheat::~Cheat()
{
}

Module Cheat::GetModule(const char* moduleName)
{
    bool exists = this->Modules.contains(moduleName);

    if (exists == true)
    {
        return Modules[moduleName];
    }

    return Module{};
}

void Cheat::LoadModules()
{
    Log(LOG_WAIT, LOG_WAIT_BUILD_MODULES);

    for (std::map<const char*, Module>::iterator it = Modules.begin(); it != Modules.end(); ++it)
    {
        this->Modules[it->first].handle = (uintptr_t)GetModuleHandle(it->second.lpName);

        if (it->second.handle)
        {
            this->Modules[it->first].loaded = true;
            Log(LOG_SUCCESS, std::format("[{}] {}", it->first, LOG_SUCCESS_BUILD_MODULE).c_str());
        }
        else
        {
            this->Modules[it->first].loaded = false;
            Log(LOG_ERROR, std::format("[{}] {}", it->first, LOG_ERROR_BUILD_MODULE).c_str());
        }
    }

    Log(LOG_SUCCESS, LOG_SUCCESS_BUILD_MODULES);
}

void Cheat::Run()
{
    LoadModules();
    BuildCheatModules();
}

void Cheat::ReloadCheatModules()
{
    BuildCheatModules();
}

void Cheat::BuildCheatModules()
{
    Log(LOG_WAIT, LOG_WAIT_BUILD_CATALOG);

    for (std::vector<CheatModule>::iterator it = CheatModules.begin(); it != CheatModules.end(); ++it)
    {
        ExecuteCheatModule(it->moduleName, it->offset, it->bypass, it->target);
    }

    Log(LOG_SUCCESS, LOG_SUCCESS_BUILT_CATALOG);
}

void Cheat::ExecuteCheatModule(const char* moduleName, int offset, LPVOID bypass, LPVOID* target)
{
    Log(LOG_WAIT, std::format("[{}+0x{:x}] {}", moduleName, offset, LOG_WAIT_LOADING_CATALOG_MODULE).c_str());

    Module module = GetModule(moduleName);
    bool hook_build_status = BuildHook(module.handle, offset, &bypass, target);

    if (hook_build_status)
    {
        Log(LOG_SUCCESS, std::format("[{}+0x{:x}] {}", moduleName, offset, LOG_SUCCESS_LOADED_CATALOG_MODULE).c_str());
        return;
    }

    Log(LOG_ERROR, std::format("[{}+0x{:x}] {}", moduleName, offset, LOG_ERROR_FAILED_CATALOG_MODULE).c_str());
}
