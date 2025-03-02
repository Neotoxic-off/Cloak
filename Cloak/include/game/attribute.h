#pragma once

#include <windows.h>
#include <iostream>
#include "MinHook.h"

struct Il2CppString {
    void* klass;
    void* monitor;
    int length;
    wchar_t chars[1];
};

class Attribute
{
    private:
        uintptr_t Assemly;

    public:
        Attribute();
        ~Attribute();

    void ForceUsername();
};

