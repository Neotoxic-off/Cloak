
#include "pch.h"

#include "game/base.h"

int __stdcall ForceZero()
{
    Log(LOG_INFO, "Forced zero");
    return 0;
}

bool __stdcall ForceTrue()
{
    Log(LOG_INFO, "Forced true");
    return true;
}

bool __stdcall ForceFalse()
{
    Log(LOG_INFO, "Forced false");
    return false;
}

int __stdcall ForceOne()
{
    Log(LOG_INFO, "Forced one");
    return 1;
}

void __stdcall ForceBypass()
{
    Log(LOG_INFO, "Forced bypass");
}
