#include "pch.h"
#include "core.h"

Core::Core()
{
	MH_Initialize();
}

Core::~Core()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

void Core::RunCheat()
{
	this->cheat.ForceHost();
	this->cheat.ForceBasementNoKeys();
	this->cheat.ForceBasementUnlocked();
	this->cheat.UnlockAllDoors();
	this->cheat.ForceNeverDead();
}

void Core::AntiCheatNoStart()
{
	this->antiCheat.NoStart();
}

void Core::HidePresence()
{
	this->presence.Hide();
}

void Core::PatchPEB()
{
	this->peb.Patch();
}


