
#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <format>

#include "utils/logger.h"
#include "utils/logs.h"

class Module
{
    public:
        MODULEINFO information;
        HMODULE handle;
        LPCWSTR pointer;
        const char* name;
        bool loaded;

        Module(const char*, LPCWSTR);
        ~Module();

        void Initialize();
};
