
#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <format>

#include "utils/logger.h"
#include "constants/logs.h"

class Module
{
    private:
        void GetInformation();

    public:
        MODULEINFO information;
        HMODULE handle;
        LPCWSTR pointer;
        uintptr_t base;
        const char* name;
        bool loaded;

        Module(const char*, LPCWSTR);
        ~Module();

        void Initialize();
};
