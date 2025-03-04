#include "pch.h"

#include "core.h"

Core::Core()
{
    this->running = true;

    MH_Initialize();
}

Core::~Core()
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}

void Core::Run()
{
    this->cheat.Run();

    std::map<int, std::function<void()>> keyActions = {
        {KEY_RELOAD_CHEAT_MODULES, [this]() { this->cheat.ReloadCheatModules(); }},
        {KEY_UNLOAD, [this]() { this->running = false; }}
    };

    while (this->running) {
        for (const auto& [key, action] : keyActions) {
            if (GetAsyncKeyState(key)) {
                action();
            }
        }
        Sleep(WAIT_KEY_INPUT_TIME);
    }
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

void Core::ApplyProtection()
{
    this->protection.Apply();
}
