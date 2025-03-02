#pragma once

#include <iostream>
#include <stdio.h>
#include <format>
#include <windows.h>
#include <tlhelp32.h>

#include "MinHook.h"
#include "pch.h"
#include "logger.h"
#include "modules/peb.h"
#include "modules/presence.h"

#include "game/anti_cheat.h"
#include "game/attribute.h"


#if _WIN64 
#pragma comment(lib, "libMinHook.x64.lib")
#else
#pragma comment(lib, "libMinHook.x86.lib")
#endif

class Core
{
	private:
		Logger logger;

		Presence presence;
		AntiCheat antiCheat;
		Attribute attribute;
		PEB peb;

		void Load();
		void Unload();
	
	public:
		Core();
		~Core();

		void BypassAntiCheat();

		void ApplySecurityModules();
		void HidePresence();
		void PatchPEB();
		void ForceUsername();
};
