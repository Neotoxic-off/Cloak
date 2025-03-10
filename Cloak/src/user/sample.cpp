#include "pch.h"

#include "user/sample.h"

Sample::Sample()
{

}

Sample::~Sample()
{

}

void Sample::Run()
{
    this->factory.cheats = {
        Cheat(MODULE_GAME_ASSEMBLY, OFFSET_SAMPLE_1, DummyZero, nullptr),
        Cheat(MODULE_GAME_ASSEMBLY, OFFSET_SAMPLE_2, DummyZero, nullptr),
        Cheat(MODULE_GAME_ASSEMBLY, OFFSET_SAMPLE_3, DummyZero, nullptr),
        Cheat(MODULE_GAME_ASSEMBLY, OFFSET_SAMPLE_4, DummyZero, nullptr),
        Cheat(MODULE_GAME_ASSEMBLY, OFFSET_SAMPLE_5, DummyZero, nullptr)
    };

    this->factory.Initialize();
}

void Sample::ReHookCheats()
{
    this->ReHookCheats();
}

void Sample::HookCheats()
{
    this->HookCheats();
}

void Sample::UnHookCheats()
{
    this->UnHookCheats();
}

void Sample::ScanPatterns()
{
    uintptr_t offset = 0;
    std::vector<const char*> patterns = {
        PATTERN_EXAMPLE_1,
        PATTERN_EXAMPLE_2
    };

    for (const char* pattern : patterns) {
        this->pattern.Scan(MODULE_GAME_ASSEMBLY, pattern);
    }
}
