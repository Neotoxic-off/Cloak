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

#include "game/cheat.h"


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
		Cheat cheat;
		PEB peb;

	public:
		Core();
		~Core();

		void HidePresence();
		void PatchPEB();

		void AntiCheatNoStart();
		void RunCheat();
};
