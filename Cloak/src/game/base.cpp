
#include "pch.h"

#include "game/base.h"

int __stdcall DummyZero()
{
    Log(LOG_INFO, "[DUMMY] Handled: zero");
    return 0;
}

bool __stdcall DummyTrue()
{
    Log(LOG_INFO, "[DUMMY] Handled: true");
    return true;
}

bool __stdcall DummyFalse()
{
    Log(LOG_INFO, "[DUMMY] Handled: false");
    return false;
}

int __stdcall DummyOne()
{
    Log(LOG_INFO, "[DUMMY] Handled: one");
    return 1;
}

void __stdcall DummySkip()
{
    Log(LOG_INFO, "[DUMMY] Handled: skip");
}
