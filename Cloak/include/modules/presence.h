#pragma once

#include <windows.h>
#include <tlhelp32.h>

#include "utils/logger.h"
#include "constants/logs.h"

class Presence
{
    public:
        Presence();
        ~Presence();

        void Patch();
};
