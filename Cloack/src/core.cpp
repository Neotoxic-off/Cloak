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
	
}

void Core::Unload()
{
	
}
