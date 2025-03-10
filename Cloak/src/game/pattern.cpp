#include "pch.h"

#include "game/pattern.h"

Pattern::Pattern()
{

}

Pattern::~Pattern()
{

}

std::vector<std::pair<BYTE, bool>> Pattern::Prepare(const std::string& pattern)
{
    BYTE value = NULL;
    std::string currentToken;
    std::vector<std::string> tokens;
    std::vector<std::pair<BYTE, bool>> result;

    for (char c : pattern)
    {
        if (c == ' ')
        {
            if (!currentToken.empty())
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        }
        else
        {
            currentToken += c;
        }
    }

    if (!currentToken.empty())
    {
        tokens.push_back(currentToken);
    }

    for (const auto& token : tokens)
    {
        if (token == "?" || token == "??")
        {
            result.push_back({ 0, false });
        }
        else
        {
            value = (BYTE)std::stoi(token, nullptr, 16);
            result.push_back({ value, true });
        }
    }

    return result;
}

uintptr_t Pattern::Find(uintptr_t moduleBase, size_t moduleSize, const std::string& pattern)
{
    auto bytePattern = Prepare(pattern);

    for (uintptr_t i = moduleBase; i < moduleBase + moduleSize - bytePattern.size(); i++)
    {
        bool found = true;

        for (size_t j = 0; j < bytePattern.size(); j++)
        {
            if (bytePattern[j].second)
            {
                if (*(BYTE*)(i + j) != bytePattern[j].first)
                {
                    found = false;
                    break;
                }
            }
        }

        if (found) return i;
    }

    return 0;
}

uintptr_t Pattern::Scan(Module* module, const char* pattern)
{
    uintptr_t offset = 0;
    uintptr_t address = 0;

    if (module->handle)
    {
        address = Find(module->base, module->information.SizeOfImage, pattern);
        if (address)
        {
            offset = address - module->base;
            Log(LOG_SUCCESS, std::format("[{}+0x{:x}]({}) {}", module->name, offset, ReducePattern(pattern), LOG_SUCCESS_SEARCHING_PATTERN).c_str());
            return offset;
        }

    }

    Log(LOG_ERROR, std::format("[{}]({}) {}", module->name, ReducePattern(pattern), LOG_ERROR_SEARCHING_PATTERN).c_str());
    return offset;
}
