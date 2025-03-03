#pragma once

#include <windows.h>
#include <tlhelp32.h>

#include "logger.h"
#include "utils/logs.h"

class Presence
{
    public:
        Presence();
        ~Presence();

        void Patch();
};
