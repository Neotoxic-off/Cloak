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
    this->factory.Initialize();

    std::map<int, std::function<void()>> keyActions = {
        {KEY_REHOOK_CHEAT_MODULES, [this]() { this->factory.ReHookCheats(); }},
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
    Log(LOG_INFO, "Cloak unloaded");
}

void Core::WaitProcess()
{
    Log(LOG_WAIT, std::format("{} {}ms", LOG_WAIT_PROCESS_LOADING, WAIT_PROCESS_LOADING_TIME).c_str());

    Sleep(WAIT_PROCESS_LOADING_TIME);
}

void Core::PatchPresence()
{
    this->presence.Patch();
}

void Core::ApplyProtection()
{
    this->protection.Apply();
}
