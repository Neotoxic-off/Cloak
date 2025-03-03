#include "pch.h"
#include "core.h"

Core::Core()
{
    MH_Initialize();
}

Core::~Core()
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}

void Core::Run()
{
    
}

void Core::WaitProcess()
{
    Log(LOG_WAIT, std::format("{} {}ms", LOG_WAIT_PROCESS_LOADING, WAIT_PROCESS_LOADING_TIME).c_str());

    Sleep(WAIT_PROCESS_LOADING_TIME);

    Log(LOG_SUCCESS, LOG_SUCCESS_PROCESS_LOADING);
}

void Core::PatchPresence()
{
    this->presence.Patch();
}

void Core::PatchDebugger()
{
    this->debugger.Patch();
}
