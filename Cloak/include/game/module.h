
#pragma once

#include <Windows.h>
#include <iostream>
#include <format>

#include "utils/logger.h"
#include "utils/logs.h"

class Module
{
    public:
        HMODULE handle;
        LPCWSTR pointer;
        const char* name;
        bool loaded;

        Module(const char*, LPCWSTR);
        ~Module();

        void Initialize();
};
