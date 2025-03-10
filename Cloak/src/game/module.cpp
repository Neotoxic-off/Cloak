#include "pch.h"

#include "game/module.h"

Module::Module(const char* name, LPCWSTR pointer)
{
    this->name = name;
    this->pointer = pointer;
    this->handle = NULL;
    this->loaded = false;
}

Module::~Module()
{

}

void Module::Initialize()
{
    Log(LOG_WAIT, std::format("[{}] {}", this->name, LOG_WAIT_BUILDING_MODULE).c_str());

    this->handle = GetModuleHandle(this->pointer);

    if (this->handle)
    {
        GetInformation();
        this->base = (uintptr_t)this->handle;
        this->loaded = true;
        Log(LOG_SUCCESS, std::format("[{}] {}", this->name, LOG_SUCCESS_BUILDING_MODULE).c_str());
        return;
    }

    this->loaded = false;
    Log(LOG_ERROR, std::format("[{}] {}", this->name, LOG_ERROR_BUILDING_MODULE).c_str());
}

void Module::GetInformation()
{
    Log(LOG_WAIT, std::format("[{}] {}", this->name, LOG_WAIT_INFORMATION_MODULE).c_str());

    GetModuleInformation(GetCurrentProcess(), this->handle, &this->information, sizeof(MODULEINFO));

    Log(LOG_SUCCESS, std::format("[{}]({}) {}", this->name, this->information.SizeOfImage, LOG_SUCCESS_INFORMATION_MODULE).c_str());
}
