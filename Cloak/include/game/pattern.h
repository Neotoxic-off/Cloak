#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>

#include "utils/logger.h"
#include "utils/tools.h"
#include "constants/logs.h"
#include "game/module.h"

class Pattern
{
    private:
        std::vector<std::pair<BYTE, bool>> Prepare(const std::string& pattern);
        uintptr_t Find(uintptr_t moduleBase, size_t moduleSize, const std::string& pattern);

    public:
        Pattern();
        ~Pattern();

        uintptr_t Search(Module* module, const char* pattern);
};
