#pragma once

#include <windows.h>
#include <iostream>

#include "minhook.h"
#include "logger.h"
#include "hooks.h"

#include "utils/settings.h"
#include "game/offsets.h"

class Cheat
{
    private:
        uintptr_t Assemly;

    public:
        Cheat();
        ~Cheat();

        void Force();
};
