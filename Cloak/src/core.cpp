#include "pch.h"
#include "core.h"

Core::Core()
{
	Load();
}

Core::~Core()
{
	Unload();
}

void Core::BypassAntiCheat()
{
	this->logger.Log(LOG_WAIT, "Bypassing anti-cheat");

	this->antiCheat.NoStart();

	this->logger.Log(LOG_SUCCESS, "Bypassed anti-cheat");
}

void Core::ApplySecurityModules()
{
	HidePresence();
	PatchPEB();
}

void Core::HidePresence()
{
	this->logger.Log(LOG_WAIT, "Hiding presence");

	this->presence.Hide();

	this->logger.Log(LOG_SUCCESS, "Hid presence");
}

void Core::PatchPEB()
{
	this->logger.Log(LOG_WAIT, "Patching debugger detection");

	this->peb.Patch();

	this->logger.Log(LOG_SUCCESS, "Patched debugger detection");
}

void Core::Load()
{
    MH_Initialize();
}

void Core::Unload()
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}
