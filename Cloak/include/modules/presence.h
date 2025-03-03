#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include "logger.h"

class Presence
{
    public:
        Presence();
        ~Presence();

        void Patch();
};
