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

void Core::RunCheat()
{
    this->cheat.Force();
}

void Core::WaitProcess()
{
    Log(LOG_WAIT, std::format("Waiting process loading {}ms", WAIT_PROCESS_LOADING_TIME).c_str());

    Sleep(WAIT_PROCESS_LOADING_TIME);
}

void Core::PatchPresence()
{
    this->presence.Patch();
}

void Core::PatchDebugger()
{
    this->debugger.Patch();
}
