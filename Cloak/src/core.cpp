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
	this->cheat.Force();
}

void Core::HidePresence()
{
	this->presence.Hide();
}

void Core::PatchPEB()
{
	this->peb.Patch();
}


