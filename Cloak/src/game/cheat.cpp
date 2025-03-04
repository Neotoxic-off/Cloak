#include "pch.h"

#include "game/cheat.h"

Cheat::Cheat()
{
}

Cheat::~Cheat()
{
}

void Cheat::LoadAssembly()
{
    Log(LOG_WAIT, LOG_WAIT_LOADING_MODULE);

    this->Assemly = (uintptr_t)GetModuleHandle(MODULE_NAME);
    this->AssemblyLoaded = false;

    if (this->Assemly)
    {
        this->AssemblyLoaded = true;
        Log(LOG_SUCCESS, LOG_SUCCESS_LOADING_MODULE);
        return;
    }

    Log(LOG_ERROR, LOG_ERROR_LOADING_MODULE);
}

void Cheat::Run()
{
    LoadAssembly();

    if (this->AssemblyLoaded == true)
    {
        Log(LOG_WAIT, "Peparing cheat modules");

        LoadCatalog();
        BuildCatalog();
        return;
    }
    Log(LOG_INFO, "Skip peparing cheat modules");
}

void Cheat::LoadCatalog()
{
    this->Catalog = {
        { this->Assemly, OFFSET_EXAMPLE, ForceTrue, nullptr }
    };

    Log(LOG_INFO, std::format("Loaded {} cheat modules", this->Catalog.size()).c_str());

}

void Cheat::BuildCatalog()
{
    Log(LOG_WAIT, std::format("Building catalog modules").c_str());

    for (std::vector<Module>::iterator it = Catalog.begin(); it != Catalog.end(); ++it)
    {
        ExecuteCatalog(it->assembly, it->offset, it->bypass, it->target);
    }

    Log(LOG_SUCCESS, std::format("Built catalog modules").c_str());
}

void Cheat::ExecuteCatalog(uintptr_t assembly, int offset, LPVOID bypass, LPVOID* target)
{
    Log(LOG_WAIT, std::format("[0x{:x}+0x{:x}] Loading catalog module", assembly, offset).c_str());

    bool hook_build_status = BuildHook(assembly, offset, &bypass, target);

    if (hook_build_status)
    {
        Log(LOG_SUCCESS, std::format("[0x{:x}+0x{:x}] Loaded catalog module", assembly, offset).c_str());
        return;
    }

    Log(LOG_ERROR, std::format("[0x{:x}+0x{:x}] Failed loading catalog module", assembly, offset).c_str());
}
