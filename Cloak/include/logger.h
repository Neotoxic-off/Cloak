#pragma once

#include <iostream>
#include <stdio.h>
#include <format>
#include <windows.h>
#include <chrono>
#include <tlhelp32.h>
#include <source_location>
#include <unordered_map>

#include "utils/settings.h"

#define LOG_WAIT "WAIT"
#define LOG_SUCCESS "DONE"
#define LOG_ERROR "ERRO"
#define LOG_INFO "INFO"

void Log(const char*, const char*);

class Logger
{
    private:
        void Load();
        void Unload();

        void DisplayHeader();

    public:
        Logger();
        ~Logger();
};
