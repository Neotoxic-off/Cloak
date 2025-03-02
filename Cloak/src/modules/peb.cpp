#include "pch.h"

#include "modules/peb.h"

PEB::PEB()
{
}

PEB::~PEB()
{
}

void PEB::Patch()
{
    Log(LOG_WAIT, "Patching debugger detection");

    PVOID pebAddress = (PVOID)__readgsqword(0x60);

    if (pebAddress) {
        BYTE* peb = static_cast<BYTE*>(pebAddress);
        peb[2] = 0;
    }

    Log(LOG_SUCCESS, "Patched debugger detection");
}
