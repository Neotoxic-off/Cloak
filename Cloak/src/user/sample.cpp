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
    this->SearchPattern();
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

void Sample::SearchPattern()
{
    this->pattern.Search(MODULE_GAME_ASSEMBLY, PATTERN_EXAMPLE);
}
