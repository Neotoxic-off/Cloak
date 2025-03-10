#include "pch.h"

#include "utils/tools.h"

std::string ReducePattern(const char* str)
{
    std::string s(str);

    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());

    return s;
}
