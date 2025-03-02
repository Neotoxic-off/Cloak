#pragma once

#include <windows.h>
#include <iostream>

#include "MinHook.h"
#include "logger.h"
#include "hooks.h"

#include "game/settings.h"
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
